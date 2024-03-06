//==============================================================================
//
// user.hpp
//
// version   : 1.0
// topic     : battleship game
// class     : C++ header
// author    : Marco Bontempi
// created   : 10-Feb-2024
//
// abstract:
//  Battleship game human player header
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

#ifndef __USER_HPP__
#define __USER_HPP__

#include "player.hpp"

// user class
//------------------------------------------------------------------------------
class user: public player
{
    public:
        // initialization
        user();

        // game play
        std::string Fire() noexcept;

    protected:
        // input methods
        std::string _Input()                        noexcept;
        bool        _IsValidInput(std::string& str) noexcept;
        void        _RunMenu()                      noexcept;
};

#endif /* __USER_HPP__ */