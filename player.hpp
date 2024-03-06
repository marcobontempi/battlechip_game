//==============================================================================
//
// player.hpp
//
// version   : 1.0
// topic     : battleship game
// class     : C++ header
// author    : Marco Bontempi
// created   : 29-Jan-2023
//
// abstract:
//  Battleship game player header
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

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <string>
#include <vector>

// battlefield size
//------------------------------------------------------------------------------
#define FIELD_ROWS 10
#define FIELD_COLS 10

// directions
//------------------------------------------------------------------------------
enum direction { dir_left = 1, dir_right = 2, dir_up = 3, dir_down = 4 };

// ship indices
//------------------------------------------------------------------------------
enum ship_index { empty_idx = 0, carrier_idx = 1, battleship_idx = 2, cruiser_idx = 3, submarine_idx = 4, destroier_idx = 5 };
enum shot_index {                miss_idx    = 1, hit_idx        = 2, sunk_idx    = 3 };

// ship features
//******************************************************************************
const std::vector<std::string> ship_name   = { "Water", "Carrier", "Battleship", "Cruiser", "Submarine", "Destroier" }; 
const std::string              ship_mark   = " cbrsd"; // ' ' = empty; 'c' = carrier; 'b' = battleship; 'r' = cruiser; 's' = submarine; 'd' = destroier;
const std::vector<int>         ship_size   = { 0, 5, 4, 3, 3, 2 };
const char                     shot_mark[] = " .xX";     // ' ' = empty; '.' = miss; 'x' = hit; 'X' = sunk;

// grid point structure
//------------------------------------------------------------------------------
//
// pos[] format:
// 
// es: "c5", "B9", "A10"
//
// pos[0]   -> char, column,
// pos[1..] -> int,  row
//
struct grid_point { int row, col; };

// player class (abstract)
//------------------------------------------------------------------------------
class player
{
    protected:
        // initialization
        player(const std::string& name);

    public:
        virtual ~player() = default;
        bool IsInitialized() const;

        // board initialization
        bool        InitRandom() noexcept;
        bool        InitShip      (int idx, std::string& pos  , int dir) noexcept;
        bool inline InitCarrier   (         std::string& pos , int dir) noexcept { return InitShip(carrier_idx,    pos, dir); }
        bool inline InitBattleship(         std::string& pos , int dir) noexcept { return InitShip(battleship_idx, pos, dir); }
        bool inline InitCruiser   (         std::string& pos , int dir) noexcept { return InitShip(cruiser_idx,    pos, dir); }
        bool inline InitSubmarine (         std::string& pos , int dir) noexcept { return InitShip(submarine_idx,  pos, dir); }
        bool inline InitDestroier (         std::string& pos , int dir) noexcept { return InitShip(destroier_idx,  pos, dir); }
        void        Reset() noexcept;
        
        // get (0-index rows and cols)
        char GetOceanGrid(int row, int col);
        char GetOceanGrid(std::string& pos);
        char GetOceanGrid(grid_point pos);

        char GetTargetGrid(int row, int col);
        char GetTargetGrid(std::string& pos);
        char GetTargetGrid(grid_point pos);

        void SetTargetGrid(std::string& pos, const char mark);

        // counters
        int CountTargetEmpty() noexcept;
        int CountTargetMiss()  noexcept;
        int CountTargetHit()   noexcept;

        // game play
        std::string Fire() noexcept;
        char        CheckShot(std::string&       pos) noexcept;

        // game end
        int  inline GetHitCounter() const noexcept { return _hit_counter; }
        bool        End();

    protected:
        // auxiliary methods
        grid_point _ParsePosition(std::string& pos);   // 0-index output
        bool       _IsValidPosition(int row, int col); // 0-index check
        bool       _IsValidPosition(grid_point& pos);  // 0-index check
        bool       _IsValidPosition(std::string& pos); // 1-index check

        // instance variables
        std::string _name;
        int         _error_condition;
        bool        _initialization;
        int         _hit_counter;
        char        _target_grid[FIELD_ROWS][FIELD_COLS]; // show the situation of the antagonist 
        char        _ocean_grid [FIELD_ROWS][FIELD_COLS]; // where player ships are positioned
};

#endif /* __PLAYER_HPP__ */