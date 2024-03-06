//==============================================================================
//
// computer.hpp
//
// version   : 1.0
// topic     : battleship game
// class     : C++ header
// author    : Marco Bontempi
// created   : 10-Feb-2024
//
// abstract:
//  Battleship game computer player header
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

#ifndef __COMPUTER_HPP__
#define __COMPUTER_HPP__

#include "player.hpp"

// computer class
//------------------------------------------------------------------------------
class computer: public player
{
    public:
        // initialization
        computer();

        // game play
        std::string Fire() noexcept;

        // get (0-index rows and cols)
        void SetTargetGrid(std::string& pos, const char mark);

    protected:
        // auxiliary methods
        void        _SetHitModeON(int row, int col) noexcept; // 0-index inputs
        bool        _EndOfHitMode()                 noexcept;
        bool        _IsMainDirection(int dir)       noexcept;
        int         _UpdateDirection(int dir)       noexcept;            
        void        _SetHitModeOFF()                noexcept;
        std::string _HitModeFire()                  noexcept;
        std::string _RandomFire()                   noexcept;

        // instance variables
        bool _hit_mode;
        int  _first_row, _first_col;
        int  _last_row,  _last_col;
        int  _dir, _dir_changes;
        int  _miss_counter, _hit_counter;
};

#endif /* __COMPUTER_HPP__ */