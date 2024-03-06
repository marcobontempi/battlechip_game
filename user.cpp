//==============================================================================
//
// user.cpp
//
// version   : 1.0
// topic     : battleship game
// class     : C++ implementation
// author    : Marco Bontempi
// created   : 10-Feb-2024
//
// abstract:
//  Battleship human player implementation
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
#include "user.hpp"
#include "functions.hpp"
#include "vt100.hpp"

// User class implementation 
//******************************************************************************
// initialization
//------------------------------------------------------------------------------
user::user() : player("User")
{}

// game play
//------------------------------------------------------------------------------
std::string user::Fire() noexcept
{
    std::cout << "\n\n\n";
    return _Input();
}

// input methods
//------------------------------------------------------------------------------
std::string user::_Input() noexcept
{
    std::string ans;
    // start an infinite loop
    do
    {
        // ask for input
        ans = ask("Insert coordinates");
        // if the user ask for a menu
        if(ans == "menu") break;
    } while(!_IsValidInput(ans));
    // return the input
    return ans;
}

//------------------------------------------------------------------------------
bool user::_IsValidInput(std::string& str) noexcept
{
// get the length of the string
  int len = str.size();
  // check if is 2, or 3
  if(len == 2)
  {
    // check for 'a' -> 'j'
    if(str[0] >= 'a' && str[0] <= 'j')
    {
      // check for '1' -> '9'
      if(str[1] >= '1' && str[1] <= '9') return true;
    }
    // check for 'A' -> 'J'
    if(str[0] >= 'A' && str[0] <= 'J')
    {
      // check for '1' -> '9'
      if(str[1] >= '1' && str[1] <= '9') return true;
    }
  }
  if(len == 3)
  {
    // check for 'a' -> 'j'
    if(str[0] >= 'a' && str[0] <= 'j')
    {
      // check for "10"
      if(str[1] == '1' && str[2] == '0') return true;
    }
    // check for 'A' -> 'J'
    if(str[0] >= 'A' && str[0] <= 'J')
    {
      // check for "10"
      if(str[1] == '1' && str[2] == '0') return true;
    }
  }
  // otherwise...
  return false;
}
