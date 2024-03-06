//==============================================================================
//
// player.cpp
//
// version   : 1.0
// topic     : battleship game
// class     : C++ implementation
// author    : Marco Bontempi
// created   : 29-Jan-2023
//
// abstract:
//  Battleship game player implementation
//
//------------------------------------------------------------------------------
// 2021-2024 by Marco Bontempi <marco.bontempi@gmail.com>.
//
// Redistribution  and   use  in   source  and  binary  forms,  with  or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source  code  must  retain the  above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form  must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in  the documentation
//    and/or other materials provided with the distribution.
// 3. Redistribution in any form  must include the references associated to this
//    code  in  the  documentation  and/or  other materials  provided  with  the
//    distribution.
//
// THIS SOFTWARE  IS PROVIDED BY THE AUTHOR AND  CONTRIBUTORS ``AS IS''  AND ANY
// EXPRESS  OR IMPLIED  WARRANTIES, INCLUDING, BUT  NOT  LIMITED TO, THE IMPLIED
// WARRANTIES  OF  MERCHANTABILITY AND  FITNESS  FOR  A  PARTICULAR PURPOSE  ARE
// DISCLAIMED. IN NO  EVENT  SHALL THE AUTHOR OR CONTRIBUTORS  BE LIABLE FOR ANY
// DIRECT,  INDIRECT,  INCIDENTAL, SPECIAL,  EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING,  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION)  HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY,  OR  TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//==============================================================================

#include "player.hpp"
#include "functions.hpp"
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <numeric>

//------------------------------------------------------------------------------
grid_point inline shift_position(grid_point pos, int row, int col)
{
    return grid_point{ pos.row + row, pos.col + col};
}

// grid functions
//******************************************************************************
void inline reset_grid(char (*board)[FIELD_COLS])
{
    for(int r = 0; r < FIELD_ROWS; ++r)
    {
        for(int c = 0; c < FIELD_COLS; ++c)
        {
            board[r][c] = ship_mark[empty_idx];
        }
    }
}

//------------------------------------------------------------------------------
void inline copy_grid(const char source[FIELD_ROWS][FIELD_COLS], char target[FIELD_ROWS][FIELD_COLS])
{
    for(int r = 0; r < FIELD_ROWS; ++r)
    {
        for(int c = 0; c < FIELD_COLS; ++c)
        {
            target[r][c] = source[r][c];
        }
    }
}

//------------------------------------------------------------------------------
void inline print_grid(const char grid[FIELD_ROWS][FIELD_COLS])
{
    std::cout << '\n';
    for(int r = 0; r < FIELD_ROWS; ++r)
    {
        std::cout << "    ";
        for(int c = 0; c < FIELD_COLS; ++c)
        {
            if(grid[r][c] == 0)
                std::cout << '.';
            else
                std::cout << grid[r][c];
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

// Player class inplementation 
//******************************************************************************
// initialization
//------------------------------------------------------------------------------
player::player(const std::string& name)
: _name(name), _error_condition(0), _initialization(false), _hit_counter(0)
{
    // initialize the battlefields
    Reset();
}

//------------------------------------------------------------------------------
bool player::IsInitialized() const
{
    return _initialization;
}

// board initialization
//------------------------------------------------------------------------------
bool player::InitRandom() noexcept
{
    int  s, N = ship_mark.size();
    std::string pos(3, ' ');
    int  dir;
    bool posed = false;
    // reset grids
    Reset();
    // scan ships
    for(s = 1; s < N; ++s)
    {
        while(true)
        {
            // extract two coordinates
            pos[0] = static_cast<char>((FIELD_COLS - 1.) * rand01()) + 'a';
            pos[1] = static_cast<char>((FIELD_ROWS - 1.) * rand01()) + '1';
            // extrack direction
            dir = (direction)(3. * rand01() + 1.);
            // add a ship
            posed = InitShip(s, pos, dir);
            if(posed) break;
        }
    }
    return true;
}

//------------------------------------------------------------------------------
bool player::InitShip(int idx, std::string& pos, int dir) noexcept
{
    // back up board
    char backup[FIELD_ROWS][FIELD_COLS];
    copy_grid(_ocean_grid, backup);
    // get ship symbol and size
    char empty = ship_mark[empty_idx];
    char mark = ship_mark[idx];
    int  size = ship_size[idx];
    int  i, j;
    // parse position
    grid_point rc0 = _ParsePosition(pos);
    grid_point rc1{ 0, 0 };
    // switch direction
    switch(dir)
    {
        case dir_right:
            for(j = 0; j < size; ++j)
            {
                // set row and col of chip element
                rc1 = shift_position(rc0, 0, j);
                if(!_IsValidPosition(rc1))
                {
                    // restore backup   
                    copy_grid(backup, _ocean_grid);
                    // return a non initialized status
                    return false;
                }
                if(_ocean_grid[rc1.row][rc1.col] != empty)
                {
                    // restore backup   
                    copy_grid(backup, _ocean_grid);
                    // return a non initialized status
                    return false;
                }
                // assign the ship element
                _ocean_grid[rc1.row][rc1.col] = mark;    
            }
            break;
        case dir_left:
            for(j = 0; j < size; ++j)
            {
                // set row and col of chip element
                rc1 = shift_position(rc0, 0, -j);
                if(!_IsValidPosition(rc1))
                {
                    // restore backup   
                    copy_grid(backup, _ocean_grid);
                    // return a non initialized status
                    return false;
                }
                if(_ocean_grid[rc1.row][rc1.col] != empty)
                {
                    // restore backup   
                    copy_grid(backup, _ocean_grid);
                    // return a non initialized status
                    return false;
                }
                // assign the ship element
                _ocean_grid[rc1.row][rc1.col] = mark;    
            }
            break;
        case dir_up:
            for(i = 0; i < size; ++i)
            {
                // set row and col of chip element
                rc1 = shift_position(rc0, -i, 0);
                if(!_IsValidPosition(rc1))
                {
                    // restore backup   
                    copy_grid(backup, _ocean_grid);
                    // return a non initialized status
                    return false;
                }
                if(_ocean_grid[rc1.row][rc1.col] != empty)
                {
                    // restore backup   
                    copy_grid(backup, _ocean_grid);
                    // return a non initialized status
                    return false;
                }
                // assign the ship element
                _ocean_grid[rc1.row][rc1.col] = mark;    
            }
            break;
        case dir_down:
            for(i = 0; i < size; ++i)
            {
                // set row and col of chip element
                rc1 = shift_position(rc0, i, 0);
                if(!_IsValidPosition(rc1))
                {
                    // restore backup   
                    copy_grid(backup, _ocean_grid);
                    // return a non initialized status
                    return false;
                }
                if(_ocean_grid[rc1.row][rc1.col] != empty)
                {
                    // restore backup   
                    copy_grid(backup, _ocean_grid);
                    // return a non initialized status
                    return false;
                }
                // assign the ship element
                _ocean_grid[rc1.row][rc1.col] = mark;    
            }
            break;
    }
    return true;
}

//------------------------------------------------------------------------------
void player::Reset() noexcept
{
    // reset the grid
    reset_grid(_ocean_grid);
    reset_grid(_target_grid);
    // reset initialization
    _initialization = false;
}

// get
//------------------------------------------------------------------------------
char player::GetOceanGrid(int row, int col)
{
    return _ocean_grid[row][col];
}

//------------------------------------------------------------------------------
char player::GetOceanGrid(std::string& pos)
{
    grid_point rc = _ParsePosition(pos);
    return GetOceanGrid(rc);
}

//------------------------------------------------------------------------------
char player::GetOceanGrid(grid_point pos)
{
    return GetOceanGrid(pos.row, pos.col);
}

//------------------------------------------------------------------------------
char player::GetTargetGrid(int row, int col)
{
    return _target_grid[row][col];
}

//------------------------------------------------------------------------------
char player::GetTargetGrid(std::string& pos)
{
    grid_point rc = _ParsePosition(pos);
    return GetTargetGrid(rc);
}

//------------------------------------------------------------------------------
char player::GetTargetGrid(grid_point pos)
{
    return GetTargetGrid(pos.row, pos.col);
}

//------------------------------------------------------------------------------
void player::SetTargetGrid(std::string& pos, const char mark)
{
    // parse the position
    grid_point pt = _ParsePosition(pos);
    // check the position
    if(_IsValidPosition(pt))
    {
        if(mark == shot_mark[empty_idx]) 
        {   
            // set miss
            _target_grid[pt.row][pt.col] = shot_mark[miss_idx];
        }
        else
        {
            // set hit
            _target_grid[pt.row][pt.col] = shot_mark[hit_idx];
            // update the hit_counter
            _hit_counter++;
        }
    }
}

// counters
//------------------------------------------------------------------------------
int player::CountTargetEmpty() noexcept
{
    char empty = shot_mark[empty_idx];
    int counter = 0;
    int i, j;
    // scan the target grid
    for(i = 0; i < FIELD_ROWS; ++i)
    {
        for(j = 0; j < FIELD_COLS; ++j)
        {
            if(_target_grid[i][j] == empty) counter++;            
        }
    }
    // return the result
    return counter;
}

//------------------------------------------------------------------------------
int player::CountTargetMiss() noexcept
{
    char miss = shot_mark[miss_idx];
    int counter = 0;
    int i, j;
    // scan the target grid
    for(i = 0; i < FIELD_ROWS; ++i)
    {
        for(j = 0; j < FIELD_COLS; ++j)
        {
            if(_target_grid[i][j] == miss) counter++;            
        }
    }
    // return the result
    return counter;
}

//------------------------------------------------------------------------------
int player::CountTargetHit() noexcept
{
    char hit = shot_mark[hit_idx];
    int counter = 0;
    int i, j;
    // scan the target grid
    for(i = 0; i < FIELD_ROWS; ++i)
    {
        for(j = 0; j < FIELD_COLS; ++j)
        {
            if(_target_grid[i][j] == hit) counter++;            
        }
    }
    // return the result
    return counter;
}

// game play
//------------------------------------------------------------------------------
std::string player::Fire() noexcept
{ 
    return std::string(); 
}

//------------------------------------------------------------------------------
char player::CheckShot(std::string& pos) noexcept
{
    // get row and col
    grid_point pt = _ParsePosition(pos);
    // if is valid...
    if(_IsValidPosition(pt))
    {
        char empty = ship_mark[empty_idx];
        // check the cell
        char mark = _ocean_grid[pt.row][pt.col];
        // update the maker in the ocean grid
        if(mark != empty)
        {
            _ocean_grid[pt.row][pt.col] = shot_mark[hit_idx];
        }
        // return the mark
        return mark; 
    }
    // return a non-valid value
    return '\0';
}

// game end
//------------------------------------------------------------------------------
bool player::End()
{
  // get the total number of hits
  int tot_hits = std::accumulate(std::begin(ship_size), std::end(ship_size), 0);
  // check the hit counter
  if(_hit_counter < tot_hits) return false;
  // if the counter is greater than tot, return true
  return true;
}

// auxiliary methods
//------------------------------------------------------------------------------
grid_point player::_ParsePosition(std::string& pos) // 0-index output
{
    // check the len
    int len  = pos.size();
    char* ch = pos.data();
    if(len == 2 || len == 3)
    {
        // parse rows and cols
        int col = (int)(std::tolower(ch[0]) - 'a');
        int row = std::atoi(ch + 1) - 1;
        // return rows and cols
        return grid_point{ row, col }; 
    }
    return grid_point{ -1, -1 };
}

//------------------------------------------------------------------------------
bool player::_IsValidPosition(int row, int col) // 0-index check
{
    if(row < 0)           return false;
    if(row >= FIELD_ROWS) return false;
    if(col < 0)           return false;
    if(col >= FIELD_COLS) return false;
    return true;
}

//------------------------------------------------------------------------------
bool player::_IsValidPosition(grid_point& pos)
{
    return _IsValidPosition(pos.row, pos.col);
}

//------------------------------------------------------------------------------
bool player::_IsValidPosition(std::string& pos)
{
    grid_point gp = _ParsePosition(pos);
    return _IsValidPosition(gp);
}

