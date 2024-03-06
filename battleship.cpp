//==============================================================================
//
// battleship.cpp
//
// version   : 1.0
// topic     : battleship game
// class     : C++ implmentation
// author    : Marco Bontempi
// created   : 13-Jan-2023
//
// abstract:
//  Battleship game and gui manager
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

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <numeric>
#include "battleship.hpp"
#include "functions.hpp"
#include "vt100.hpp"

// battlefield figure
//******************************************************************************
#define BOARD_ROWS 12
#define BOARD_COLS 70

//------------------------------------------------------------------------------
char battle_board[BOARD_ROWS][BOARD_COLS] = 
{
 //         1         2         3         4         5         6          
 //123456789012345678901234567890123456789012345678901234567890123456789 
  "           A B C D E F G H I J                 A B C D E F G H I J   ",
  "        01       ~             01           01| | | | | | | | | | |01",
  "        02   ~               ~ 02           02| | | | | | | | | | |02",
  "        03             ~       03           03| | | | | | | | | | |03",
  "        04                 ~   04           04| | | | | | | | | | |04",
  "        05     ~               05           05| | | | | | | | | | |05",
  "        06                     06           06| | | | | | | | | | |06",
  "        07             ~       07           07| | | | | | | | | | |07",
  "        08         ~           08           08| | | | | | | | | | |08",
  "        09   ~                 09           09| | | | | | | | | | |09",
  "        10     ~             ~ 10           10| | | | | | | | | | |10",
  "           A B C D E F G H I J                 A B C D E F G H I J   "
};

// battleship
//******************************************************************************
// initialization
//------------------------------------------------------------------------------
battleship::battleship()
: _error_condition(0), _initialized(false), _user(), _computer(), _quit_flag(false)
{}

// gui
//------------------------------------------------------------------------------
void battleship::Welcome() const
{
  if(_error_condition == 0)
  {
    std::cout << '\n';  
    std::cout << "    * * * * * * * * * * * * * * * * * * * *\n";  
    std::cout << "    *                                     *\n";  
    std::cout << "    *    B A T T L E S H I P  G A M E     *\n";
    std::cout << "    *                                     *\n";  
    std::cout << "    * * * * * * * * * * * * * * * * * * * *\n";  
    std::cout << '\n';
    std::cout << "    vesion 1.0                      \n";
    std::cout << '\n';
    std::cout << "    by Marco & Samuele Bontempi     \n";
    std::cout << std::endl;
  }
}

// game board initialization
//------------------------------------------------------------------------------
void battleship::InitBoard()
{
  // reset boards
  _user.Reset();
  _computer.Reset();
  // initialize computer
  _initialized &= _computer.InitRandom();
  // initialize human
  while(1)
  {
    std::string ans = ask("Choose manual or automatic grid initialization (m, a)");
    if(ans.size() == 1)
    {
      if(ans[0] == 'a' || ans[0] == 'A')
      {
        _initialized = _UserAutoInit();
        return;
      }
      if(ans[0] == 'm' || ans[0] == 'M')
      {
        _initialized = _UserManualInit();
        return;
      }
    }
  }
}

// game play
//------------------------------------------------------------------------------
void battleship::Play()
{
  if(IsInitialized())
  {
    std::string pos;
    char mark;
    while(true)
    {
      // user turn
      _UpdateBoard();
      pos  = _user.Fire();
      if(pos == "menu")
      {
        _RunMenu();
        // exit the game
        if(_quit_flag) break;
        // re-ask input
        continue;
      }
      mark = _computer.CheckShot(pos);
      _user.SetTargetGrid(pos, mark);
      if(_user.End())
      {
        Winner("User");
        break;
      }
      // computer turn
      _UpdateBoard();
      pos  = _computer.Fire();
      mark = _user.CheckShot(pos);
      _computer.SetTargetGrid(pos, mark);
      if(_computer.End())
      {
        Winner("Computer");
        break;
      }
    }
  }
  else
  {
    std::cerr << "The battlefield was not initialized. Game aborted." << std::endl;
  }
}

// end game
//------------------------------------------------------------------------------
void battleship::Winner(const std::string& name)
{
  _UpdateBoard();
  std::cout << "\n\n\n\n";
  std::cout << "***\n";
  std::cout << "*** The winner is: " << name << "!!! ***\n";
  std::cout << "***\n";
  std::cout << "\n\n\n\n" << std::endl;
}

// auxiliary functions
//------------------------------------------------------------------------------
void battleship::_SetOceanGrid(int row, int col, char mark)
{
  // row and col are 0-index coordinates
  //
  // set the battle board coordinates
  char empty = ship_mark[empty_idx];
  //char miss  = shot_mark[miss_idx];
  int bb_row =  1 + row;
  int bb_col = 11 + 2 * col;
  if(mark != empty)
  {
//    if(mark == miss)
//      battle_board[bb_row][bb_col] = '.';
//    else
      battle_board[bb_row][bb_col] = mark;
  }
}

//------------------------------------------------------------------------------
void battleship::_SetTargetGrid(int row, int col, char mark)
{
  // row and col are 0-index coordinates
  //
  // set the battle board coordinates
  char empty = ship_mark[empty_idx];
  int bb_row =  1 + row;
  int bb_col = 47 + 2 * col;
  if(mark != empty) battle_board[bb_row][bb_col] = mark;
}

//------------------------------------------------------------------------------
void battleship::_UpdateBoard()
{
  // make the battleboard
  int i, j;
  for(i = 0; i < FIELD_ROWS; ++i)
  {
    for(j = 0; j < FIELD_COLS; ++j)
    {
      _SetOceanGrid( i, j, _user.GetOceanGrid(i, j));      // compile ocean grid
      _SetTargetGrid(i, j, _user.GetTargetGrid(i, j));     // compile target grid
      _SetOceanGrid( i, j, _computer.GetTargetGrid(i, j)); // overlap computer target grid
    }
  }
  // print the battleboard
  std::cout << clear_screen;
  for(int i = 0; i < BOARD_ROWS; ++i)
  {
    std::cout << battle_board[i] << '\n';
  }
  std::cout << std::endl;
}

//------------------------------------------------------------------------------
bool battleship::_UserAutoInit()
{
  return _user.InitRandom();
}

//------------------------------------------------------------------------------
bool battleship::_UserManualInit()
{  
  std::stringstream msg;
  int  s, N = ship_mark.size();
  std::string pos;
  int  dir;
  std::string ans;
  bool init = false;

  // loop ships
  for(s = 1; s < N; ++s)
  {  
    while(1)
    {
      _UpdateBoard();
      // ask for ship position
      msg.str("");
      msg << "\n\n\n\nChoose " << ship_name[s] << " (" << ship_size[s] << ") position and direction";
      ans = ask(msg.str());
      // get position substring
      pos = ans.substr(0, ans.size() - 1);
      // parse direction
      switch(*(ans.end() - 1))
      {
        case 'l': dir = dir_left;  break;
        case 'r': dir = dir_right; break;
        case 'u': dir = dir_up;    break;
        case 'd': dir = dir_down;  break;
      }
      // initialize the ship
      init = _user.InitShip(s, pos, dir);
      // check if the initialization is successfull
      if(init) break;
    }
  }
  return true;
}

//------------------------------------------------------------------------------
void battleship::_RunMenu() noexcept
{
  // initialize the answer
  int ans = 0;
  // start a loop
  while(1)
  {
    // print the menu
    std::cout << clear_screen;
    std::cout << "\n\n\n\n";
    std::cout << "    ----------------------------------------------\n";
    std::cout << "    Main Menu:\n";
    std::cout << "    ----------------------------------------------\n";
    std::cout << "    \n";
    std::cout << "    1) statistics\n";
    std::cout << "    2) info\n";
    std::cout << "    3) return to game\n";
    std::cout << "    4) reset game\n";
    std::cout << "    5) quit game\n";
    std::cout << "    \n";
    std::cout << "    ----------------------------------------------\n";
    std::cout << "    \n";
    std::cout << "    select funtction: ";
    std::cin >> ans;
    // select the answer
    switch(ans)
    {
      case 1: // statistics
        _Statistics();
        ask("return to main menu (ok)");
        break;
      case 2: // info
        Welcome();
        ask("return to main menu (ok)");
        break;
      case 3: // return to game
        return;
        break;
      case 4: // reset game
        InitBoard();
        return;
        break;
      case 5: // quit game
        _quit_flag = true;
        std::cout << clear_screen;
        return;
        break;
    }
  }
}

//------------------------------------------------------------------------------
void battleship::_Statistics() noexcept
{
  int total_ships = std::accumulate(ship_size.begin(), ship_size.end(), 0);
  int usr_empty = _user.CountTargetEmpty(),    usr_miss = _user.CountTargetMiss(),    usr_hit = _user.CountTargetHit(),    usr_all = (100 * usr_hit) / total_ships;
  int  pc_empty = _computer.CountTargetEmpty(), pc_miss = _computer.CountTargetMiss(), pc_hit = _computer.CountTargetHit(), pc_all = (100 * pc_hit)  / total_ships;

  // print the table
  std::cout << clear_screen;
  std::cout << "\n\n";
  std::cout << "               |    empty   |   miss   |   hit   |   overall performance   \n";
  std::cout << "    =======================================================================\n";
  std::cout << "               |            |          |         |                         \n";
  std::cout << "    User       |    " << std::setw(5) << usr_empty << "   |   " << std::setw(4) << usr_miss << "   |   " << std::setw(3) << usr_hit << "   |   " << std::setw(17) << usr_all << " % \n";
  std::cout << "               |            |          |         |                         \n";
  std::cout << "    Computer   |    " << std::setw(5) << pc_empty  << "   |   " << std::setw(4) << pc_miss  << "   |   " << std::setw(3) << pc_hit  << "   |   " << std::setw(17) << pc_all  << " % \n";
  std::cout << "               |            |          |         |                         \n";
  std::cout << "    =======================================================================\n";
  std::cout << '\n' << std::endl;
}
