//==============================================================================
//
// battleship.hpp
//
// version   : 1.0
// topic     : battleship game
// class     : C++ header
// author    : Marco Bontempi
// created   : 13-Jan-2023
//
// abstract:
//  Battleship game and gui manager header
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

#ifndef __BATTLESHIP_HPP__
#define __BATTLESHIP_HPP__

#include "user.hpp"
#include "computer.hpp"

// battleship class
class battleship
{
    public:
        // initialization
        battleship();
        bool IsInitialized() { return _initialized; }

        // gui
        void Welcome() const;
        
        // game board initialization
        void InitBoard();

        // game play
        void Play();

        // end game
        void Winner(const std::string& name); 

    private:
        // auxiliary functions
        void _SetOceanGrid(int row, int col, char mark);
        void _SetTargetGrid(int row, int col, char mark);
        void _UpdateBoard();
        
        bool _UserAutoInit();
        bool _UserManualInit();

        void _RunMenu()   noexcept;
        void _Statistics() noexcept;

        // instance variables
        int      _error_condition;
        bool     _initialized;
        user     _user;
        computer _computer;
        bool     _quit_flag;
};

#endif /* __BATTLESHIP_HPP__ */