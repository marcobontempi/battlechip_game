//==============================================================================
//
// computer.cpp
//
// version   : 1.0
// topic     : battleship game
// class     : C++ implementation
// author    : Marco Bontempi
// created   : 10-Feb-2024
//
// abstract:
//  Battleship computer player implementation
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

#include <sstream>
#include <iostream>
#include "computer.hpp"
#include "functions.hpp"

//------------------------------------------------------------------------------
std::string make_position(int row, int col) // 0-index input
{
    std::stringstream pos;
    pos << static_cast<char>(col + 'a') << (row + 1);
    return pos.str();
}

// User class implementation 
//******************************************************************************
// initialization
//------------------------------------------------------------------------------
computer::computer() 
: player("Computer"), _hit_mode(false), _first_row(-1), _first_col(-1), _last_row(-1), _last_col(-1), _dir(dir_left),_dir_changes(0), _miss_counter(0), _hit_counter(0)
{;}

// game play
//------------------------------------------------------------------------------
std::string computer::Fire() noexcept
{
    // check if the hit mode was active
    if(_hit_mode) 
    {
        return _HitModeFire();
    }
    // else return a random position
    return _RandomFire();
}

//------------------------------------------------------------------------------
void computer::SetTargetGrid(std::string& pos, const char mark)
{
    char empty = shot_mark[empty_idx];
    // parse the input
    grid_point gp = _ParsePosition(pos);
    
    // check if hit mode is active
    if(_hit_mode)
    {
        // check for empty or ship
        if(mark == empty)
        {
            // update the muss counter
            _miss_counter++;
            // change direction
            _dir = _UpdateDirection(_dir);
            // reset the last position
            _last_row = _first_row;
            _last_col = _first_col;
            // disable the hit mode
            if(_EndOfHitMode()) _SetHitModeOFF();
        }
        else
        {
            // store the position
            _last_row = gp.row;
            _last_col = gp.col;
            // increment the hit counter
            _hit_counter++;
        }
    }
    else
    {
        // check for empty or ship and activate the hit_mode
        if(mark != empty) _SetHitModeON(gp.row, gp.col);
    }
    // run the parent method
    player::SetTargetGrid(pos, mark);
}

// auxiliary methods
//------------------------------------------------------------------------------
void computer::_SetHitModeON(int row, int col) noexcept // 0-index inputs
{
    // initialize direction
    _dir = dir_left;
    _dir_changes = 0;
    // initialize first position
    _first_row = row;
    _first_col = col;
    // initialize the last position
    _last_row = row;
    _last_col = col;
    // reset the bounds counter
    _miss_counter = 0;
    _hit_counter = 1;
    // set the hit mode to 'true'
    _hit_mode = true;

    // std::cout << "Set hit mode ON" << std::endl;
}

//------------------------------------------------------------------------------
bool computer::_EndOfHitMode() noexcept
{
    bool hc = (_hit_counter  > 1);
    bool mc = (_miss_counter > 1);
    bool dr = (_dir_changes  > 0);
    return (hc & mc & dr);
}

//------------------------------------------------------------------------------
bool computer::_IsMainDirection(int dir) noexcept
{
    return (_hit_counter > 1);
}

//------------------------------------------------------------------------------
int computer::_UpdateDirection(int dir) noexcept            
{
    // update the dir changes counter
    _dir_changes++;
    // if is a main direction
    if(_IsMainDirection(dir))
    {
        // select a specific direction
        switch(dir)
        {
            case dir_left:  return dir_right;
            case dir_right: return dir_left;
            case dir_up:    return dir_down;
            case dir_down:  return dir_up;
        }
    }
    // else increment the direction
    return (dir % 4) + 1;
}

//------------------------------------------------------------------------------
void computer::_SetHitModeOFF() noexcept
{
    // reset direction
    _dir = dir_left;
    _dir_changes = 0;
    // reset first position
    _first_row = -1;
    _first_col = -1;
    // reset the last position
    _last_row = -1;
    _last_col = -1;
    // reset the bounds counter
    _miss_counter = 0;
    _hit_counter = 0;
    // set the hit mode to 'false'
    _hit_mode = false;

    // std::cout << "Set hit mode OFF" << std::endl;
}

//------------------------------------------------------------------------------
std::string computer::_HitModeFire() noexcept
{
    int row, col;
    // define empty cell
    char empty = shot_mark[empty_idx];
    char hit   = shot_mark[hit_idx];
    // make an infinite loop until a valid position was found
    while(1)
    {
        switch(_dir)
        {
            case dir_left:
                col = _last_col - 1;
                row = _last_row;
                break;
            case dir_right:
                col = _last_col + 1;
                row = _last_row;
                break;
            case dir_up:
                col = _last_col;
                row = _last_row - 1;
                break;
            case dir_down:
                col = _last_col;
                row = _last_row + 1;
                break;
        }

        //std::cout << "computer = " << row << ", " << col << "; dir = " << _dir << std::endl;

        // check if the position is valid
        if(_IsValidPosition(row, col)) 
        {
            // check if the position was previously set
            if(_target_grid[row][col] == empty) 
                break;
            else if(_target_grid[row][col] == hit)
            {
                _hit_counter++;
                _last_col = col;
                _last_row = row;
            } 
            else // if is miss
            {
                _miss_counter++;
                _dir = _UpdateDirection(_dir);
                // check if the ship was sunk 
                if(_EndOfHitMode())
                {
                    // disable the hit mode
                    _SetHitModeOFF();
                    // return a random fire
                    return _RandomFire();
                }
            }
        }
        else
        {
            // simulate a miss shot
            _miss_counter++;
            // try an other direction
            _dir = _UpdateDirection(_dir);
            // check if the ship was sunk 
            if(_EndOfHitMode())
            {
                // disable the hit mode
                _SetHitModeOFF();
                // return a random fire
                return _RandomFire();
            }
        }
    }
    // return the position
    return make_position(row, col);
}


//------------------------------------------------------------------------------
std::string computer::_RandomFire() noexcept
{
    // define empty cell
    char empty = shot_mark[empty_idx];
    // set the range
    double max_rows = FIELD_ROWS - 1.;
    double max_cols = FIELD_COLS - 1.;
    int row, col;
    // make an infinite loop until a valid position was found
    while(1)
    {
        // generate the position
        row = static_cast<int>(max_rows * rand01());
        col = static_cast<int>(max_cols * rand01());
        // check if the position is valid
        if(_IsValidPosition(row, col)) 
        {
            // check if the position was previously set
            if(_target_grid[row][col] == empty) 
                break;
        }
    }
    // return the position
    return make_position(row, col);
}
