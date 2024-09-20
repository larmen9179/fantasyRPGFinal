#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <thread>
#include "main.h"
#include "player.h"
#include "enemy.h"
#pragma comment(lib, "winmm.lib")

#define NOMINMAX
#include <Windows.h>


//declaring global game map
std::vector<std::vector<std::string>> dungeon = 
{   
    //change the player back to the starting room
    //room 3 - possible to encounter (3) enemies
    {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1"},
    {"-1", "-1", "-1", "-1", "3", "3", "3", "3", "3", "b", "3", "-1"},
    {"-1", "-1", "3", "3", "3", "3", "t", "3", "3", "3", "3", "-1"},
    {"-1", "3", "3", "3", "3", "3", "3", "3", "3", "3", "3", "-1"},
    {"-1", "3", "3", "c", "3", "3", "3", "3", "3", "3", "c", "-1"},
    {"-1", "3", "3", "-1", "-1", "-1", "3", "w", "3", "3", "-1", "-1"},
    {"-1", "3", "3", "-1", "-1", "-1", "3", "3", "3", "-1", "-1", "-1"},
    
    //room 2 - possible to encounter (2) enemies
    {"-1", "2", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1"},
    {"-1", "2", "2", "2", "2", "w", "-1", "2", "c", "2", "-1", "-1"},
    {"-1", "-1", "2", "2", "2", "2", "-1", "-1", "-1", "2", "2", "-1"},
    {"-1", "c", "2", "2", "-1", "m", "2", "2", "2", "2", "2", "-1"},
    {"-1", "-1", "2", "t", "-1", "2", "2", "2", "2", "2", "2", "-1"},

    //room 1 encounters just one enemy
    {"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "1", "-1"},
    {"-1", "-1", "c", "1", "1", "1", "1", "1", "1", "1", "w", "-1"},
    {"-1", "1", "1", "-1", "t", "1", "-1", "-1", "1", "c", "-1", "-1"},
    {"-1", "s", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1"}
 };

//global player object
Player player("Roghbradden", dungeon); 

//pickupable weapons/items/magic
std::vector<Weapon> pickupableWeapons = { Weapon("Crossbow", 6, 11, {
    "                                                   ",
    "                  *++#                             ",
    "                  ##==##                           ",
    "                  ##*:  ##                         ",
    "                   ##+--  ##                       ",
    "                    ##*--   ##     +               ",
    "                     ##*--     #*=+#*              ",
    "                      ##*==*##*+=*#                ",
    "                       ###+==-=+*# ##              ",
    "                         #+=+++  #   ##            ",
    "                        ===*##+===     ###         ",
    "                        =+*####%#=--     ###       ",
    "                      =+*###   ####*=--     ##     ",
    "                    ==+###        #####+===== ##   ",
    "                  ====##%             ######*****  ",
    "                 ===+#%@                     ##    ",
    "                ==+*#%@                            ",
    "              ====###                              ",
	"             ++*###                                ",
    "           +++*##                                  ",
    "         +++*#                                     ",
    "        *++#                                       ",
    "       #*+#                                        ",
    "       #                                           ",
	"                                                   "
    }), Weapon("Axe", 4, 8, {
    "                                                   ",
    "                                 ##                ",
    "                                 ####              ",
    "                                  ##** *           ",
    "                                  ####***          ",
    "                                  ###****#         ",
    "                                 ###*####**#       ",
    "                               ####*######*+**     ",
    "                              %%## ######=--=+     ",
    "                             %###   ###*+=--       ",
    "                           %%##     #*+===*        ",
    "                         %%##      #*+=--          ",
    "                       %%##        *==             ",
    "                     #%##        *+=+              ",
    "                   #%%##                           ",
    "                  %%#                              ",
    "                %%%#                               ",
    "              %%###                                ",
    "             %%##                                  ",
    "           %%##                                    ",
    "         %%%#                                      ",
    "        %##                                        ",
    "      ####                                         ",
    "       #                                           ",
    "                                                   "
    }), Weapon("Sword", 2, 5, {
    "                                                ",
    "                                               #",
    "                                             ###",
    "                                          **#%  ",
    "                                        +++#%   ",
    "                                      +=+*#%    ",
    "                                    *=+###      ",
    "                                  *=*####       ",
    "                                ++*##**         ",
    "                              #+**##+           ",
    "                            *+++**+             ",
    "                           ++***+               ",
    "                         +++#++                 ",
    "                       *++#*++                  ",
    "                     *++###*                    ",
    "                   *++*%#*                      ",
    "                  **#***                        ",
    "         ==+*  #******                          ",
    "           #+##*#**#                            ",
    "            @#*#*#                              ",
    "           @@@@#+=@                             ",
    "         @@%#@  @==+                            ",
    "        %%#%      **                            ",
    "     %##%@                                      ",
    "     #*+*                                       ",
    "                                                "
    })};
std::vector<Weapon> pickupableMagic = {Weapon("Icestorm", 3, 12, {
    
    "                                                   ",
    "                      +  *  =                      ",
    "                      *%%%%%#                      ",
    "             *# +     @@@%@%@     + #*             ",
    "             #%%#     *@@@@%#     #@%#             ",
    "          #+ *@%@ *    %%@@#    ##%%@* **          ",
    "      ++  %#   *%@@     *@*     @@%*   %%@ #*      ",
    "       %@@@@@#   **##   *%*   %#*#   *@@@@@#       ",
    "      #%%--#@@    *%**  @@@  *+%#    @@#=-#%*      ",
    "      *##@@@+-*%%   @.*@ @ @#.@   #*=:=@@@%%#      ",
    "          #% %@=: .*  -=@@@+:#@*. :=@@  #          ",
    "                @%*-#@@@+*=@@@#:*%@                ",
    "                   %@:@+=@=+@:@@                   ",
    "                   %@:@+=@=+@:@@                   ",
    "                @%*:*%@@+*=@@@#:*%@                ",
    "          #% %@=: .*@ -=@@@+:#@*. :=@@  #          ",
    "      *##@@@+-*%%   @.*@ @ @#.@   #*=:=@@@%%#      ",
    "      #%%--#@@    *%**  @@@  *+%#    @@#=-#%*      ",
    "       %@@@@@#   **##   *%*   %#*#   *@@@@@#       ",
    "      ++  %#   *%@@     *@*     @@%*   %%@ #*      ",
    "          #+ *@%@ *    %%@@#    ##%%@* **          ",
    "             #%%#     *@@@@%#     #@%#             ",
    "             *# +     @@@%@%@     + #*             ",
    "                      *%%%%%#                      ",
    "                      +  *  =                      ",
	"                                                   "
    
    }), Weapon("Lightning", 2,9, {
    
	"												    ",
    "                           #@                      ",
    "                         =++@                      ",
    "                      ===**#                       ",
    "                      :=##+                        ",
    "                      =:-+@                        ",
    "                     @==*%                         ",
    "                    @::++#=                        ",
    "                  *#:.:++==                        ",
    "                :==:..**=                          ",
    "              .:=+:..-#*#                          ",
    "              :+*....:-+**++==                     ",
    "             ==##-......::+=+==:=                  ",
    "              +%@@@+:--:.....-+%@#++               ",
    "               =====@%##=-:....-==+*@              ",
    "                       %##%+...:++==               ",
    "                         @#=-:-*+=                 ",
    "                       ===:.::@@                   ",
    "                      ==-=-*@@@                    ",
    "                      @@=:=*@                      ",
    "                      %*-%#=                       ",
    "                      @+%%=                        ",
    "                     @%%@                          ",
    "                     %@@                           ",
    "                     @                             ",
	"												    "
    
    }), Weapon("Fireball", 1, 3, {
    "                                                   ",
	"                                                   ",
    "                 .--                               ",
    "                  -=-@                             ",
    "                       =@@                         ",
    "                                                   ",
    "                       @   @                       ",
    "                    .. @.  @                       ",
    "                   =+      @@   .                  ",
    "                  @@@    .  @ --= -@#.             ",
    "                  @ @@ @@  @@ %   +@               ",
    "               -. =    %  :@ #@   +                ",
    "               :@ @=  .  @@@ @@@ %@@               ",
    "                    @ -=@#   - @ -@%               ",
    "              =@    +@ #.+   *@@* @                ",
    "             @#=    *-++*@%= %@+@#@                ",
    "             #+.% : @@ .# @@#+%:+ *                ",
    "             *@ =@= #  =: @: @ @*-*@               ",
    "             *@@  .-= +..:    :% +@%               ",
    "            :=%@+@.-%@:=@=-.= @**@@%-              ",
    "              =@@-*=##*.  * =@@@=@%#.              ",
    "               *@@*#@     *:@%=:+@#=               ",
    "                #@@.#@ :*+  @@%@@%+                ",
    "                =#@*@+**  .%*=@@#=                 ",
    "                 =%@@*@@@@@@@@@#=                  ",
    "                  :=+*%@@@%*+==                    ",
    "                        *:                         ",
    "                                                   "
    
    })};
std::vector<Item> pickupableItems = {Item("Vitality-Potion", 1, 0, 7, {
    "                                        ",
    "                                        ",
    "              +++                       ",
    "              +++  +++ +++              ",
    "                *  +++                  ",
    "                   ++                   ",
    "                                        ",
    "                +++###%%                ",
    "              %%%%      %%              ",
    "              %%%%%## %%                ",
    "                 % +  %                 ",
    "                %% ++%%                 ",
    "                %%   %%                 ",
    "                %%%  %%                 ",
    "               %%%    %%%%%             ",
    "             %%%%    **##%%%            ",
    "            %%% ++  **#### %%           ",
    "            %%#*******+**##%%           ",
    "           %%%****+******##%%           ",
    "           %%#***++*****###%%           ",
    "           %%%*******+*###%%            ",
    "            %%%%**######%%%             ",
    "               %%%%%%%%%%               ",
    "                                        "
    
    }), Item("Smokebomb", 1, 0, 0, {
    
    "                                        ",
    "@@@        @@@@@@@                      ",
    "@@@@@@@  @@@@@@@@@@                     ",
    "@@@@@@@@@@@@@@@@@@@                     ",
    "@@@@@@@@@@@@@@@@@@@@@                   ",
    "  @@@@   @@@     @@@@                   ",
    "       @@@@@@@  @@@@@                   ",
    "    @@@@@@@@@   @@@@@ @@@@@             ",
    "    @@@@@       @@@@@@@    @            ",
    "    @@@@                    @@          ",
    "                    ----=++*@#%%        ",
    "                  -:--#*+*****##%@      ",
    "                -::--=+##*****###%@     ",
    "               -::-==+****@@#*###%%@    ",
    "              ----=+*********%@@%%%%@   ",
    "              ---=+#######****##%%%@@   ",
    "              --=+##%%%%%%###%%%@@@@@   ",
    "              ==*##%%%%%%%%%%@@@@@@@@   ",
    "              +*##%@@@@@@@@@@@@@@@@@    ",
    "               %%%@@@@@@@@@@@@@@@@@     ",
    "                @@@@@@@@@@@@@@@@@@      ",
    "                  @@@@@@@@@@@@@@        ",
    "                     @@@@@@@@           ",
    "                                        "
    
    }), Item("Throwing-Knives", 1, 15, 0, {
    "                                        ",
    "                                        ",
    "                                        ",
    "                                 %@     ",
    "                            --:-#@      ",
    "                          =---:#%@      ",
    "                        ----::#*#       ",
    "                       --=:::@%#        ",
    "                      -+*=::###         ",
    "                     -****-@#           ",
    "                   @#+***=@*            ",
    "                  %=***++*              ",
    "               %%++**+:#                ",
    "              %*****+#                  ",
    "               %****+                   ",
    "             @%##++*@                   ",
    "            @%**+                       ",
    "           %*@@-                        ",
    "         @#@@+-                         ",
    "        @#**=-                          ",
    "       @%%#-                            ",
    "       @%=-                             ",
    "                                        ",
    "                                        "
    })};

//images for upgrades to print in corresponding methods
std::vector<std::string> weaponUpgrade = {
    "                                             ",
    "                                      +.     ",
    "             #                     *:-       ",
    "      #*     ###      :     *#######*+       ",
    "    -+*####*+=.  .%@@@+.:+******######       ",
    "    #    .#@@@@@@@@@@@@@@%- :=*++*####%      ",
    "   -@@@@@  -+=.         :*@@@%%#%*++###      ",
    "   %*.%@@@@   +##########=. @@##%%@#*###+    ",
    "     =:#@*@@@*   =#########.@@@#**####**#    ",
    "     *+:@@-#@@@@@     :####+  @@%#==+++=     ",
    "     %#*:@@=@@%-#@@@@@   -###: @@%%***+-     ",
    "     @@@*:@%@@*- @.%:@@@@  .##: @@@@@@@@-    ",
    "      :+@#+@*@@%+@#.@@  -@@   #. -@@#@@@+    ",
    "       --@#=@% @# @@@ =@  -@@   =. @@%@%%%+  ",
    "       *=+@#+@#*@@@  :***+   @@%    @@#%%#   ",
    "       #*==#@%@=- @ @+**####+  -@@   @@#%%   ",
    "      +##*++=%@@@@@   :           @@  %@=-   ",
    "     .*###*++==#**@@@@@@@@@@@@@ @+%+@@@@@    ",
    "     .#*####+*++@@@*==+#+==:. *%@@@@*-.      ",
    "         ####****+@@@@@%%##%%%%%%%%@@@@@     ",
    "         ####*##*+   *@@# #@@@@+             ",
    "         ####                                ",
    "                                             " 
};
std::vector<std::string> magicUpgrade = {
    "                                             ",
    "                     :                       ",
    "                     +-       ----           ",
    "                      +:     *%%%%-     :.   ",
    "     .=.    ::      .##+     =*%%%=     .    ",
    "            ..       :==      -#%%=          ",
    "                       =      -%#%*=         ",
    "        :+-- -.:==:  -=+:.    =%%%#*=        ",
    "         ##@@@##*++=---=*#+- -+#%%%###+:     ",
    "        :%%%#*=:-@@@@@@@::-**#########*:     ",
    "  -.     :...:@@@@@%@@@@@@@=-+###+. .-.      ",
    "  =++::      @@@@++%%#-%-+@@@++#+            ",
    "   =%%#=     @@%-@@@#*%%+@=*@@=#+            ",
    "    +%#*=.:=-@%##@+%@@@@+*@*%@=#+- ..        ",
    "     :=*####-@*@+@=%.:#@+@#+%@-#####%-   :   ",
    "       #####=@@@#@@@@@@%##+%@@-######:   :   ",
    "      =+####+@@%@++#%*+*+*@@@#+####%*        ",
    "   .+*%%%###*+#@@@@@@@#@@@@%  =###%%+        ",
    "  -*%%%*=:=+#*+=#%@%@@@@#.    -###%%*+--     ",
    " -*%%#*-   -###**++====+=     :%%%%%%%%%-    ",
    " -%%*=      *#######%###:      =#%%%%%%%-    ",
    " -%%*        .-::=+#*=::    -   :--=*#%*.    ",
    " -*%=             .-       -*-       --.     ",
    "  =#=                       -.               ",
    "   :                                         ",
    "                                             "
};
std::vector<std::string> defenseUpgrade = {
    "                                             ",
    "                        =--=---*             ",
    "                      ++*####%#**=           ",
    "                    .=+%%%%%##@%%#+=++#.     ",
    "                    =##%%#%#%####%@####      ",
    "                    -*#%%#%#%##%#%@@@@       ",
    "                     =+###%%%%%#%#####@#+-   ",
    "                      *%#%###@%##%#@%%%#%-   ",
    "                 %%%*%#@#%**%%#%%%#####*+.   ",
    "            =#@#+.:.:-=@@@  +@#%%%##%%@#     ",
    "         . @@@+=*#%###*++:+ -=+*%%#%###**    ",
    "          *-.--@#=**##*##*-%    -%@##%%#*.   ",
    "        :  -=-=*:%@**+=+*%+*-   -@%##%%@%    ",
    "    #-%@@@*#*@@+*@@@@@@@-#@..+  #####*@#-.   ",
    "    # +: @*%*+*@%**:= +@=#=*#  :#####% %     ",
    "      -.@*@+@# @@:-+==@*-@##   -####@**      ",
    "       -+#@#@-@++@+-=@%#@-      +*%*@#+      ",
    "         #.%*@%=+ +@@@@@+        +%%%#+      ",
    "          @%%::=@@@@@#-+:         *%%%#=     ",
    "           %@@@@@- .=***@@        --=+##*-   ",
    "          #*+.--::.. :+=:.+           .-=--  ",
    "        +::+:.%. *@*@@: %                    ",
    "       : ..  #@%@@                           ",
    "        *%#@@%                               ",
    "                                             "
};

//image for map to print when picked up
std::vector<std::string> mapPickup = {
    "                                             ",
    "                    :-++++:      .:          ",
    "                  +****#********++#++        ",
    "                -=*********#*##*****+::      ",
    "               #*******#*%#**#*##***%#**=    ",
    "              =%*#*****##****#****+:   .:    ",
    "             -**#***#*##*%**#*#**+           ",
    "            =**#*****%*****#*#**+            ",
    "           =******##******##***+             ",
    "           ***#*******####****+              ",
    "          -*******%*******#*#+               ",
    "         -+**##***#**##*#***#:               ",
    "         +***##*****##*#*#*@*                ",
    "        .#*#*#****##**###**#                 ",
    "         **#***#****###*###-                 ",
    "        :*****#####**#*#**-                  ",
    "   .+*-.=#####************:                  ",
    "     =+#*###****####%%#*=-                   ",
    "                   -+++-                     ",
    "                     .                       ",
    "                                             "
};

//image for chest to print when picked up
std::vector<std::string> chestPickup = {
    "                                             ",
    "                          @#%                ",
    "                #%#%@*   @ .#                ",
    "               %=**##*@*@@*@@                ",
    "               @*%%%%#@##%%@#*%%@            ",
    "              %+#%@%%#@%@@@@@%%%%##@%        ",
    "              @=@@@%#@@%@@@@@@@@@%%#*+@@@    ",
    "              +@  @@@*#%@@@@@@@@@@@%@@-=:*   ",
    "            @@@*@#    @%#%@@@@@@@@@@@@+%*=*  ",
    "          #@@@*+@:=  .= @@@@%%@@@@@@@=#@#*+@ ",
    "       *#*@-%==+ @:  % ==+: @@%@@@@@%+**+@-@ ",
    "   +##@@@  @@##       @%+%*#:@#%%%@@**@+#%@% ",
    " %@@@@@+-.*+..@@@       *#**- @%%%@#-@:*@%   ",
    " @=-@@@@%# ***=*.:%-*@ @%%@%+= @%#% %@@      ",
    " @.-%:.-@@@@@@##%*@+   . @@**%  @@@@         ",
    " @:@@*%#==::-@@@@@@##%@@@@#= @@@%:@%         ",
    " @@***@@*###*=..=-#@@@+-*@@@*+==*+@@         ",
    " #@ +%###@##*#@@#*+=-=@@%@%=**#@@=@@         ",
    "   @@: --+###@###@@##.@=-+*@@##*@#%@         ",
    "      @@@+ -@%+*#**#%*@=@@#*##%++-**         ",
    "         @@@ :%@%+***:@*=*###*=.@@           ",
    "            @@@ .*@@%=@*@@*+-+@              ",
    "               @@@  :-%==:=@@                ",
    "                  @@@@@-%#                   ",
    "                      @=                     ",
    "                                             "
};

//image for boss to print
std::vector<std::string> bossImage = {
    
    "                                                      ",
    "                                        .*#@@%        ",
    "                                    #@%@%@@           ",
    "                                -@@*---=*%@  .        ",
    "         :#               . .*@@%=-==--=. %#          ",
    "         -+           :-=.=%@#: .=*=#@@@@@@+:         ",
    "         *=.        .+.:=+-. #@@@%%@%*+==:            ",
    "         -*..      .=-%+@*@@@  .==*==+*+#=            ",
    "         *%:- #       .+#*..+@@-.*+==++:+:            ",
    "          * :*#*.      ::#*-:**@*.-*+=+#**            ",
    "          --:=**:      + *%*-=:+@@--=+*@@.            ",
    "           #=--**=.     =++#+++-+@@=+#@+         +    ",
    "            +.:+#+.     +@=-@:*%@@@@-=                ",
    "             :+.++%      #%*@@.#=:.@@                 ",
    "              =+==#:   :@=*=:@*:-:.:@        :@       ",
    "              -%*-%=: --#=--: @=#@%=         .%       ",
    "               #**@#*=++###%@%@@@%            %       ",
    "       -+.    =%**#+*#%#+*@@###*##=:           =      ",
    "       #==-.-+*#*+#+#**+%@+#*+++++++-.         ::     ",
    "        *#%#.**+++####+#*#+##=#*++=-*=*        -@     ",
    "      -*##%-%@*=%#+%*%@@*-#**+@%%**+*   *%     +@     ",
    "     +:=+*#*@%#+**%%**=#@*%*==*@@@@#     #*===#:-     ",
    "    :-*#@@##--#=@*+%%   -@@@*%+:##%-      -#+@+:      ",
    "    :**+*=. *+   +*#=    @@@@+%+-**                   ",
    "   .+#*=++@@@*    #:    :=+*   %#*%                   ",
    "  %.+*+-  #+    :@             ..                     ",
    "  . :=                                                ",
    "  @@*                                                 ",
    "                                                      "

};

//clonable enemy objects
std::vector<Enemy> enemies;

//rate for enemy encounters at each dungeon location that's not a specified room
int enemyEncounter{};

//stores the amount of gold the player has
int gold{};

//store the player's defense level, and damage levels for magic and weapons
int defenseLevel{};

int magicLevel{};
int weaponLevel{};

//tells if the player actually switched rooms last turn
bool transition = false;

int main()
{

    mciSendString(TEXT("open \"audio\\fantasyTheme.mp3\" type mpegvideo alias theme"), NULL, 0, NULL);
    mciSendString(TEXT("play theme repeat"), NULL, 0, NULL);
    mciSendString(TEXT("setaudio theme volume to 25"), NULL, 0, NULL);

    //giving the player their first weapon (fists)
    std::string firstWeapon = "Fists";


    //-------------TESTING-------------------------------

    //giving the player the map early to test print map functionality
    player.setHasMap(true);

    //--------------------------------------------
    

    //adding the weapon to the player's inventory
    player.addWeapon(firstWeapon, 100, 100, {});

    //setting the player's current weapon to the first weapon
    player.setCurrentWeapon(firstWeapon);


    //----------TESTING---------------------------
    //Testing logic for magic attacks

    //std::string firstMagic = "Fireball";
    //player.addMagic(firstMagic, 1, 3, {});
    
    //player.setCurrentMagic(firstMagic);

    //--------------------------------------------
   

    //-----------TESTING---------------------------
    //Testing logic for items

    std::string firstItem = "Throwing-Knives";
    std::string secondItem = "Vitality-Potion";
    std::string thirdItem = "Smokebomb";
    player.addItem(firstItem, 1, 15, 0, {});
    player.addItem(secondItem, 1, 0, 7, {});
    player.addItem(thirdItem, 1, 0, 0, {});

    //--------------------------------------------

    /*

    //temporarily storing the Enemy ascii art as a raw string literal
    enemies.push_back(Enemy("Goblin", 5, 1, R"(                                                  
                                                  
1                  =======-===-                    
2                -====++====++==-=-                
3               -====+*****+++=====-=              
4              -*#=-+#%%%%%#*+-===+=-=             
5             #@%#++*#%@@@@@@*=+++-+=-==           
6            *@%%%*=+*%@@@@@@#=**+++++===          
7           -++-%@#+**###%%%%+=#*+=++==+=          
8           =++-*##*##%###*==-**+=+*+++++=         
9           +*=*++++*#%##***+-=*#*+++++++          
0           =+*+*==+++##@@%*++--#*#**+**+          
1           ++##++*++*#@@@@@#%#*+#******           
2           **###**#*+%@@@@**%##%%**+*+            
3            +##***++*%@@%=-=+*#%+*+++             
4           ==***==++*+**+=+++##*+++               
5            ##**#%##*****####%%###                
6             ##%%%##%                             
    )"));
     */

    //adding the enemies to the enemies vector
    enemies.push_back(Enemy("Goblin", 6, 2, 3, {
        "                                        ",
        "                             %%         ",
        "         %%%%%%%%        %%%%           ",
        "           %%%%%  % %%%%% %%%           ",
        "               %%### %-% %%             ",
        "                 #*++===#%              ",
        "        %*        #%+#%%                ",
        "        #*:       %#                    ",
        "         *-*     % ## ***               ",
        "          *- *   *#%#*#  %              ",
        "        **%%% *** #*%**#  %             ",
        "           %%%   %%    %   %%%          ",
        "           %%%  %  *%#*                 ",
        "                  *# %** *              ",
        "                  *    %                ",
        "                   *    %               ",
        "                  %*#                   ",
        "              %%%%       %              ",
        "                          %%%%%         ",
        "                                        "
        }));
    enemies.push_back(Enemy("Merman", 12, 3, 4, {
        "     ###                                ",
        "      #  #         *#                   ",
        "  ### ## ##     **+=                    ",
        "  ##  ## ##   **###*+++                 ",
        "  ##  ## #  ##       #*+==              ",
        "  # ###   *#    #**      *+*            ",
        "     ##  ##*            ** **           ",
        "     ##       ###* **#*** ****          ",
        "     ##     ##       *#  *    *         ",
        "     ##      ########    ****  *        ",
        "     ##       ##  **     ** #*          ",
        "    ###**####*  *#*       ** #  *       ",
        "     ## *      *##        *#*# #*       ",
        "     ##  #*#    **# **#***# **###       ",
        "     ##         ****#**#*#  ###**  #### ",
        "     ##         #*#     **# **     #*#  ",
        "     ##           **#   * * ***#*#**    ",
        "     ##         **#**# #* #*##  *#*##   ",
        "     ##         **  ## ##* #       ##   ",
        "     ##       #*#      **  #*           "
        }));
    enemies.push_back(Enemy("Kobold", 10, 4, 5, {
        "                                        ",
        "                                        ",
        "                                  ++    ",
        "                                  ++    ",
        "      ##                        ++#     ",
        "     %   ### ####             *+%       ",
        "       %%   %%%%#%           *+%        ",
        "     #####%% %%  ##          %+++       ",
        "        *** **    +##        %%+++      ",
        "            %#***++  +*%      %%%++%    ",
        "              ##%++ +#  +*##+   +*+*#   ",
        "             %**+ ++**#      +#  *+*+#  ",
        "      %      %+++++*****     ++%% %+ *  ",
        "+++%%       % ++   **%        ++*%*+ %  ",
        " **%##+++ %%      %    %%%   **+++   %  ",
        "  ***     %++#  ++%%#*++*   #*** %% %   ",
        "                 **     %% %%%%%%%%%    ",
        "                *##      %% %%          ",
        "           **#%%%%%  *****  %           ",
        "                                        "
        }));

    //calling the main game loop
    gameLoop();
    return 0;
}

int getRand(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

void printPlayerStats() {
    std::cout << "Current Health: " << player.getHealthPoints() << '\n';
    std::cout << "Total Gold: " << gold << '\n';
}

void drawWeapon(std::vector<std::string>& weaponImage) {
	for (auto& line : weaponImage) {
		std::cout << line << '\n';
	}
    std::cout << '\n';
}

void drawSpell(std::vector<std::string>& spellImage) {
	for (auto& line : spellImage) {
		std::cout << line << '\n';
	}
	std::cout << '\n';
}
void eventHandler(const std::vector<int> &playerPosition){

    //weapon room (for gaining new weapons)
    if (dungeon[playerPosition[0]][playerPosition[1]] == "w") {

        std::cout << "You have found the " << pickupableWeapons.back().name << "...\n";

        //draw weapon in terminal
        drawWeapon(pickupableWeapons.back().image);

        player.addWeapon(pickupableWeapons.back().name, pickupableWeapons.back().minDmg, pickupableWeapons.back().maxDmg, pickupableWeapons.back().image);

        pickupableWeapons.pop_back();

        std::cout << "Type \"Enter\" to continue...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        
    }
    //totem room (for gaining new spells)
    else if (dungeon[playerPosition[0]][playerPosition[1]] == "t") {

        if (pickupableMagic.back().name == "Fireball") {
            player.setCurrentMagic(pickupableMagic.back().name);
        }

		std::cout << "You have found the " << pickupableMagic.back().name << " spell...\n";

        //draw spell in terminal
        drawSpell(pickupableMagic.back().image);

		player.addMagic(pickupableMagic.back().name, pickupableMagic.back().minDmg, pickupableMagic.back().maxDmg, pickupableMagic.back().image);

		pickupableMagic.pop_back();

        std::cout << "Type \"Enter\" to continue...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    //map room
    else if (dungeon[playerPosition[0]][playerPosition[1]] == "m") {
        std::cout << "You've found the map...\n";
        player.setHasMap(true);

        drawMap();

        std::cout << '\n';
        std::cout << "Type \"Enter\" to continue...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    //chest room
	else if (dungeon[playerPosition[0]][playerPosition[1]] == "c") {
		
        //giving the player a random amount of gold from each chest found
        std::cout << "You've found a chest...\n";

        drawChest();

		int gAmount = getRand(3, 29);

		std::cout << "You got " << gAmount << " gold...\n";

        //updating the player's total gold from the value generated
        gold += gAmount;

        //waiting in the console for 2 seconds
        std::this_thread::sleep_for(std::chrono::seconds(2));

        //generating a drop chance for character upgrades
        int dropChance = getRand(1, 9);

        //gives the player more defense (reduced damage from enemies attacks)
        if (dropChance <= 3) {
            std::cout << "You've found an armor piece...\n";
            drawUpgrade("defense");
            std::cout << "Your defense level has increased...\n";



            defenseLevel++;

        }
        //gives the player more magic damage
        else if (dropChance >= 4 && dropChance <= 6) {
            std::cout << "You've found a magical relic...\n";
            drawUpgrade("magic");
            std::cout << "Your magic damage has increased...\n";
            magicLevel++;

        }
        //gives the player more weapon damage
        else if(dropChance >= 7 && dropChance <= 9){
            std::cout << "You're found an enchanted shard...\n";
            drawUpgrade("weapon");
            std::cout << "Your weapon damage has increased...\n";
            weaponLevel++;
            
		}

        std::cout << "Type \"Enter\" to continue...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

	}
    else if (dungeon[playerPosition[0]][playerPosition[1]] == "b") {
        bossEvent();
    }

    dungeon[playerPosition[0]][playerPosition[1]] = "1";
}

void bossEvent() {
    clearScreen();
    std::cout << "WELCOME TO MY LAIR...\n";

	std::cout << '\n';

    std::cout << "Type \"Enter\" to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    std::string userInput;

    int turns = 2;

    Enemy boss("Dragon", 75, 5, 9, {});

    while (boss.getHealthPoints() > 0) {
        clearScreen();
        drawBoss(boss);

        std::cout << '\n';

        printPlayerStats();

        std::cout << "Enter a command or type 'help' for a list of commands...\n";
        std::cout << ">";
        std::cin >> userInput;

        if (userInput == "help") {
            std::cout << "Commands: \n";
            std::cout << "a - attack\n";
            std::cout << "u - use item\n";
            std::cout << "i - inventory\n";
            std::cout << "c - change equipment\n";


            std::cout << '\n';
            std::cout << "Type \"Enter\" to continue...\n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
        else if (userInput == "a") {
            std::cout << '\n';
            std::cout << "Attack the dragon with current weapon or magic?\n";
            std::cout << "Type in your option number...\n";
            std::cout << '\n';

            std::cout << "1 - Weapon\n";
            std::cout << "2 - Magic\n";
            std::cout << "3 - Go back...\n";

            std::cout << '\n';

            //grabbing the users choice
            std::cin >> userInput;

            if (userInput == "1") {
                int damage = getRand(player.getWeapon(player.getCurrentWeapon()).minDmg, player.getWeapon(player.getCurrentWeapon()).maxDmg);

                std::cout << "You attack the dragon with " << player.getCurrentWeapon() << "...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));

                std::cout << "You have dealt " << damage << " damage to the dragon...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));

                boss.takeDamage(damage);
                turns--;
            }
            else if (userInput == "2") {

                int damage = getRand(player.getMagic(player.getCurrentMagic()).minDmg, player.getMagic(player.getCurrentMagic()).maxDmg);

                std::cout << "You cast " << player.getCurrentMagic() << "...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));

                std::cout << "You have dealt " << damage << " damage to the dragon...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));

                boss.takeDamage(damage);

                turns--;
            }
            else if (userInput == "3") {
                continue;
            }
            else {
                std::cout << "Invalid option... Please try again...";

				std::cout << "Type \"Enter\" to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

                continue;
            }

            //bosses turn to attack
            if (turns == 0) {
				int damage = getRand(boss.getMinDamage(), boss.getMaxDamage());

                std::cout << '\n';
                std::cout << "The dragon attacks you for " << damage << " damage...";
                std::this_thread::sleep_for(std::chrono::seconds(2));

                player.takeDamage(damage);
                turns = 2;
            }

            if (player.getHealthPoints() <= 0) {
                std::cout << '\n';
                clearScreen();
                std::cout << "You have been defeated by the dragon\n";
                std::cout << "The game has ended!\n";

                drawDeath();

                std::cout << '\n';

                std::cout << "Type \"Enter\" to exit...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

                exit(0);
            }
        }
        else if (userInput == "u") {
            int emptyItems{};
            std::vector<std::string>usableItems;
            
			for (auto& item : player.getItems()) {
				if (item.amount < 1) {
					emptyItems++;
				}
                else if (item.amount > 0) {
                    usableItems.push_back(item.name);
                }
			}

            if(player.getItems().empty() || emptyItems == player.getItems().size()){
                std::cout << "You don't have any items to use...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                
                continue;
			}
            else{
                std::cout << '\n';

				for (auto& item : player.getItems()) {
                    if (item.amount > 0) {
						std::cout << item.name << " - Amount: " << item.amount << '\n';
                    }
				}

                std::cout << '\n';
				std::cout << "Use which item?\n";
                std::cout << '\n';

                std::cin >> userInput;

                if (std::find(usableItems.begin(), usableItems.end(), userInput) != usableItems.end()) {

                    if (userInput == "Vitality-Potion") {
                        if (player.getHealthPoints() == player.getMaxHealth())
                            std::cout << "You are already at full health...";
                        else {
                            turns--;
                            int healAmount = getRand(4, 10);
                            player.getItem("Vitality-Potion").amount--;
                            player.heal(healAmount);
                            std::cout << "You have healed for " << healAmount << " health points...\n";
                        }

                        std::cout << '\n';

                        std::cout << "Type \"Enter\" to continue...\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                    }
                    else if (userInput == "Smokebomb") {
                        player.getItem("Smokebomb").amount--;

                        std::cout << "You use a smokebomb to blind the dragon...\n";
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        std::cout << "You gain an extra turn...\n";
                        turns++;
                    }
                    else if (userInput == "Throwing-Knives") {
                        turns--;

                        player.getItem("Throwing-Knives").amount--;

                        boss.takeDamage(4);

                        std::cout << "You throw knives and hit the dragon for 4 damage...\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(2500));

                        std::cout << '\n';

                    }
                }
                else {
                    std::cout << "Invalid item... Please try again...\n";
					std::this_thread::sleep_for(std::chrono::seconds(2));
					continue;
                }

            }
        }
        else if (userInput == "i") {
            showInventory();
        }
		else if (userInput == "c") {
            showInventory();

            std::cout << "Enter a command to change equipment: \n";

            std::cout << "w - change weapon\n";
            std::cout << "m - change magic\n";
            std::cout << "g - go back\n";
            std::cout << '\n';

            std::cin >> userInput;

            if (userInput == "w") {
                std::cout << '\n';
                std::cout << "Equip which weapon? \n";
                std::cout << '\n';

                for (auto& weapon : player.getWeapons()) {
                    std::cout << weapon.first << '\n';
                }

                std::cout << '\n';

                std::cin >> userInput;

                if (player.getWeapons().find(userInput) != player.getWeapons().end()) {
                    player.setCurrentWeapon(userInput);
                    std::cout << "You have equipped the " << userInput << "...\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    continue;
                }
                else {
                    std::cout << "Invalid weapon. Please try again...\n";
                    std::cout << "Type \"Enter\" to continue...\n";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    continue;
                }
            }
            else if (userInput == "m") {
                std::cout << '\n';
				std::cout << "Equip which spell? \n";
                std::cout << '\n';

				for (auto& spell : player.getSpells()) {
					std::cout << spell.first << '\n';
				}

                std::cout << '\n';

                std::cin >> userInput;

                if (player.getSpells().find(userInput) != player.getSpells().end()) {
                    player.setCurrentMagic(userInput);
					std::cout << "You have equipped the " << userInput << " spell...\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    continue;
                }
                else {
					std::cout << "Invalid spell. Please try again...\n";
					std::cout << "Type \"Enter\" to continue...\n";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();
					continue;
                }
            }
            else if (userInput == "g") {
                continue;
            }
            else {
				std::cout << "Invalid option... Please try again...";

				std::cout << "Type \"Enter\" to continue...\n";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin.get();
                continue;
            }
		}
        else {
			std::cout << "Invalid command... Please try again...\n";
			
			std::cout << "Type \"Enter\" to continue...\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
			continue;
        }
    }

    win();
}

void win(){

    clearScreen();

	std::cout << "You have defeated the dragon...\n";
	std::cout << "You have won the game!\n";

	std::cout << '\n';

	std::cout << "Type \"Enter\" to exit...\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	exit(0);
}

void drawBoss(Enemy & boss) {
    for (int i = 0; i < dungeon.size() * 3; i++)
        std::cout << "-";
    
    for (auto& line : bossImage) 
		std::cout << line << '\n';

    std::cout << "Dragon Health: " << boss.getHealthPoints() << '\n';

    for (int i = 0; i < dungeon.size() * 3; i++) 
        std::cout << "-";
}

void drawUpgrade(std::string upgrade) {
	if(upgrade == "weapon") {
		for(auto& line : weaponUpgrade) {
			std::cout << line << '\n';
		}
	}
	else if (upgrade == "magic") {
		for(auto& line : magicUpgrade) {
			std::cout << line << '\n';
		}
	}
    else if (upgrade == "defense") {
        for (auto& line : defenseUpgrade) {
            std::cout << line << '\n';
        }
    }
}

void drawMap() {
    for(int i = 0;i < mapPickup.size(); i++) {
		std::cout << mapPickup[i] << '\n';
	}
}

void drawChest(){
    for(int i = 0; i < chestPickup.size(); i++) {
        std::cout << chestPickup[i] << '\n';
    }
}

void gameLoop() {

    

    //user input for commands
    std::string userInput;
    //storing the player's starting position
    //this will be used to update the player's position
    //passed by reference to the moveHandler function
    //passed by reference to the printDungeon function
    //passed by reference to the inputHandler function
    std::vector<int> playerPosition = playerStart();

    while (true) {

        //clearing terminal screen
        clearScreen();

        if (!eventRoom(playerPosition)) {
            

            if (transition) {
                std::cout << "You have switched rooms...\n";
                std::cout << "You could encounter an enemy in this room...\n";
                int randNumber = getRand(0, 50);

                std::cout << randNumber << '\n';
                std::cout << enemyEncounter << '\n';

                if (randNumber <= enemyEncounter) {
                    std::cout << "You have encountered an enemy...\n";

                    fight(playerPosition);

                    std::cout << "enemy encounter rate is reset\n";

                    enemyEncounter = 0;
                }
                else {
					std::cout << "You have not encountered an enemy...\n";
                    std::cout << "enemy encounter rate is increased\n";
                    enemyEncounter++;
				}
            }
            else {
                std::cout << "You are still in the same room...\n";
                std::cout << "you wont encounter an enemy...\n";
            }
        }
		else {
            eventHandler(playerPosition);
            clearScreen();
		}

        transition = false;

        //printing the dungeon map
        printDungeon(playerPosition);

        std::vector<bool> possibleMoves = moveFinder(playerPosition);

        //printing player stats
		printPlayerStats();

        //prompting for user input
        std::cout << "Enter a command or type 'help' for a list of commands...\n";
        std::cout << ">";

        //reading user input
        std::cin >> userInput;

        //handling user input commands
        inputHandler(userInput, playerPosition, possibleMoves);

    }
}

void drawDeath() {

    std::vector<std::string> deathImage = {
        "                                                  ",
        "                  =======-===-                    ",
        "                -====++====++==-=-                ",
        "               -====+*****+++=====-=              ",
        "              -*#=-+#%%%%%#*+-===+=-=             ",
        "             #@%#++*#%@@@@@@*=+++-+=-==           ",
        "            *@%%%*=+*%@@@@@@#=**+++++===          ",
        "           -++-%@#+**###%%%%+=#*+=++==+=          ",
        "           =++-*##*##%###*==-**+=+*+++++=         ",
        "           +*=*++++*#%##***+-=*#*+++++++          ",
        "           =+*+*==+++##@@%*++--#*#**+**+          ",
        "           ++##++*++*#@@@@@#%#*+#******           ",
        "           **###**#*+%@@@@**%##%%**+*+            ",
        "            +##***++*%@@%=-=+*#%+*+++             ",
        "           ==***==++*+**+=+++##*+++               ",
        "            ##**#%##*****####%%###                ",
        "             ##%%%##%                             ",
        "                                                  "
    };

    for(auto& line : deathImage) {
		std::cout << line << '\n';
	}

}

void fight(std::vector<int> &playerPosition) {
    
    bool ran = false;
    //removing the previous screen showing dungeon map
    clearScreen();

    //empty vector of enemies for the player to fight
    std::vector<Enemy> enemiesToFight;

    //getting the number of enemies to fight in the room
    int enemyCount = std::stoi(dungeon[playerPosition[0]][playerPosition[1]]);

    //cloning a random enemy from the enemies vector and adding it to the enemiesToFight vector
    for(int i = 0;i < enemyCount; i++) {
        int enemyChoice = getRand(0, enemyCount - 1);

        std::cout << "You have encountered a " << enemies[enemyChoice].getName() << "...\n";

        enemiesToFight.push_back(Enemy(enemies[enemyChoice].getName(), enemies[enemyChoice].getHealthPoints(), enemies[enemyChoice].getMinDamage(), enemies[enemyChoice].getMaxDamage(), enemies[enemyChoice].getImage()));
	}

    std::cout << '\n';

    int aliveEnemies{countEnemies(enemiesToFight)};
    int turnsLeft{2};

    int enemiesFell{};

	while (aliveEnemies > 0) {
        //drawing the ascii enemies
        drawEnemies(enemiesToFight);

        //checking if the player has any turns left
        //if not, then all the enemies attack the player
        //terminal messages will be enemy attacking and damage amount dealt
        
        std::cout << "Current Health: " << player.getHealthPoints() << '\n';
		std::string userInput;
		std::cout << "Enter a command or type 'help' for a list of commands...\n";
		std::cout << ">";

		std::cin >> userInput;

		if (userInput == "help") {
			std::cout << "Commands: \n";
			std::cout << "a - attack\n";
            std::cout << "u - use item\n";
            std::cout << "i - inventory\n";
            std::cout << "c - change equipment\n";
			std::cout << "r - run away\n";
			

			std::cout << '\n';
			std::cout << "Type \"Enter\" to continue...\n";

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
		}
		else if (userInput == "a") {

            int enemyToAttack{};
			
            attackEnemy:

                //prompt message for the user to attack an enemy
                std::cout << '\n';
                std::cout << "Attack what? Type in your option number...";
                std::cout << '\n';

                int i{};

                //listing the possible enemies to attack(fixed)
                for(auto &enemy : enemiesToFight) {
					if(enemy.getHealthPoints() > 0) {
						std::cout << i + 1 << " - " << enemy.getName() << '\n';
						i++;
					}
				}

                //giving the user a go back option
                i++;
                std::cout << i << " - Go back...\n";
                std::cout << '\n';

                //grabbing user option
                std::cin >> userInput;

                std::vector<int> enemyOptions;

                int j = 1;
                //storing the options for the user to attack based off of the enemies that are still alive(fixed)
                for (auto& enemy : enemiesToFight) {
                    if (enemy.getHealthPoints() > 0) {
                        enemyOptions.push_back(j);
                        j++;
                    }
                }
                
                //checking if the user wants to go back
                if(userInput == std::to_string(i)) {
                    std::cout << '\n';
                    std::cout << "Going back to battle menu...";

                    std::cout << '\n';
                    std::cout << "Type \"Enter\" to continue...\n";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();

				    goto clear;
			    }

                else if(userInput.length() == 1 && std::isdigit(userInput[0])){
                    if (std::find(enemyOptions.begin(), enemyOptions.end(), std::stoi(userInput)) != enemyOptions.end()) {
                        enemyToAttack = std::stoi(userInput) - 1;

                        std::cout << "You have chosen to attack the " << enemiesToFight[enemyToAttack].getName() << "...\n";

                        goto attackType;
                    }
                    else {
                        std::cout << "Invalid option. Please try again...\n";
                        std::cout << "Type \"Enter\" to continue...\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();

                        clearScreen();
                        drawEnemies(enemiesToFight);

                        goto attackEnemy;
                    }
                }
                else {
					std::cout << "Invalid option. Please try again...\n";
					std::cout << "Type \"Enter\" to continue...\n";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();
                    
                    clearScreen();
                    drawEnemies(enemiesToFight);

					goto attackEnemy;
				}
            
            //label for the user to choose the type of attack they want to use
            attackType:

                //prompt message for the user to choose the type of attack
                std::cout << '\n';
                std::cout << "Attack with current weapon or magic? Type in your option number...\n";

                std::cout << "1 - Weapon\n";
                std::cout << "2 - Magic\n";
                std::cout << "3 - Go back...\n";

                std::cout << '\n';

                //grabbing the users choice
                std::cin >> userInput;

                //allowing the user to go back to menu to choose a different enemy
                if (userInput == "3") {
                    std::cout << '\n';
					std::cout << "Going back to enemy menu...";

					std::cout << '\n';
					std::cout << "Type \"Enter\" to continue...\n";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();

                    clearScreen();
                    drawEnemies(enemiesToFight);

                    goto attackEnemy;
                }
                else if (userInput == "1") {

                    turnsLeft--;

                    std::cout << "You attack the " << enemiesToFight[enemyToAttack].getName() << " with " << player.getWeapon(player.getCurrentWeapon()).name;

                    int attackDamage = getRand(player.getWeapon(player.getCurrentWeapon()).minDmg, player.getWeapon(player.getCurrentWeapon()).maxDmg);

                    //adding the player's weapon damage level to the attack damage
                    attackDamage += weaponLevel;

                    enemiesToFight[enemyToAttack].takeDamage(attackDamage);

                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::cout << '\n';

                    std::cout << "You have dealt " << attackDamage << " damage to the " << enemiesToFight[enemyToAttack].getName() << '\n';

                    if (enemiesToFight[enemyToAttack].getHealthPoints() <= 0) {
						enemiesToFight.erase(enemiesToFight.begin() + enemyToAttack);
                        enemiesFell++;
                    }

                    std::this_thread::sleep_for(std::chrono::seconds(2));

                }
                else if (userInput == "2") {
                    if (!player.hasMagic()) {
                        std::cout << "You don't have any magic yet...\n";
                        std::cout << "Going back to attack menu...\n";

                        std::cout << '\n';

                        std::cout << "Type \"Enter\" to continue...\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                        clearScreen();
                        drawEnemies(enemiesToFight);

                        goto attackType;
                    }

                    turnsLeft--;

                    std::cout << "You cast " << player.getMagic(player.getCurrentMagic()).name;

                    int attackDamage = getRand(player.getMagic(player.getCurrentMagic()).minDmg, player.getMagic(player.getCurrentMagic()).maxDmg);

                    //adding the player's magic damage level to the attack damage
                    attackDamage += magicLevel;

                    enemiesToFight[enemyToAttack].takeDamage(attackDamage);

                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::cout << '\n';

                    std::cout << "You have dealt " << attackDamage << " damage to the " << enemiesToFight[enemyToAttack].getName() << '\n';

                    if (enemiesToFight[enemyToAttack].getHealthPoints() <= 0) {
                        enemiesToFight.erase(enemiesToFight.begin() + enemyToAttack);
                        enemiesFell++;
                    }

                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
                else {

                    std::cout << "Invalid option. Please try again...\n";
					std::cout << "Type \"Enter\" to continue...\n";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();

					clearScreen();
					drawEnemies(enemiesToFight);

					goto attackType;
                }
                    
		}
		else if (userInput == "r") {
			std::cout << "You have successfully ran away!\n";
            ran = true;
			break;
		}
		else if (userInput == "i") {
			showInventory();
		}
        else if (userInput == "c") {
            showInventory();

            goto changeE;

            changeE:
                std::cout << "Change Equipment: \n";

                std::cout << '\n';

                std::cout << "Enter a command to change equipment: \n";
                std::cout << "w - change weapon\n";
                std::cout << "m - change magic\n";
                std::cout << "g - go back\n";
                std::cout << '\n';

                std::cin >> userInput;

                if (userInput == "w") {
                    goto weaponE;
                }
                else if (userInput == "m") {
                    goto magicE;
                }
                else if (userInput == "g") {
                    goto end;
                }
                else {
                    std::cout << "Invalid command. Please try again...\n";

                    std::cout << "Type \"Enter\" to continue...\n";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();

                    clearScreen();
                    drawEnemies(enemiesToFight);
                    std::cout << "Current Health: " << player.getHealthPoints() << '\n';

                    goto changeE;
                }

            weaponE:
                std::cout << '\n';
                std::cout << "Equip which weapon? \n";
                std::cout << '\n';

                for (auto& weapon : player.getWeapons()) {
                    std::cout << weapon.first << '\n';
                }

                std::cout << '\n';

                std::cin >> userInput;

                if (player.getWeapons().find(userInput) != player.getWeapons().end()) {
                    player.setCurrentWeapon(userInput);
                    std::cout << "You have equipped the " << userInput << "...\n";
                    goto end;
                }
                else {
                    std::cout << "Invalid weapon. Please try again...\n";
                    std::cout << "Type \"Enter\" to continue...\n";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();

                    clearScreen();
                    drawEnemies(enemiesToFight);
                    std::cout << "Current Health: " << player.getHealthPoints() << '\n';

                    goto weaponE;
                }

            magicE:
                std::cout << '\n';
                std::cout << "Equip which spell? \n";
                std::cout << '\n';

                for (auto& spell : player.getSpells()) {
                    std::cout << spell.first << '\n';
                }

                std::cout << '\n';

                std::cin >> userInput;

                if (player.getSpells().find(userInput) != player.getSpells().end()) {
                    player.setCurrentMagic(userInput);
                    std::cout << "You have equipped the " << userInput << "...\n";
                }
                else {
                    std::cout << "Invalid spell. Please try again...\n";
                    std::cout << "Type \"Enter\" to continue...\n";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();

                    clearScreen();
                    drawEnemies(enemiesToFight);
                    std::cout << "Current Health: " << player.getHealthPoints() << '\n';

                    goto magicE;
                }

            end:
                std::cout << "Going back to menu...\n";
                std::cout << "Type \"Enter\" to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();


        }
        else if (userInput == "u") {

            int emptyItems{};

			for (auto& item : player.getItems()) {
                if (item.amount < 1) {
                    emptyItems++;
                }
			}

            if (player.getItems().empty() || emptyItems == player.getItems().size()) {
                std::cout << "You don't have any items to use...\n";

                std::cout << '\n';

                std::cout << "Type \"Enter\" to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

            }
            else{
                    
                itemChoice:
                    std::cout << '\n';

                    std::vector<std::string> usableItems;

                    for(auto &item: player.getItems()) {
                        if(item.amount > 0) {
                            usableItems.push_back(item.name);
						    std::cout << item.name << " - Amount: " << item.amount << '\n';
					    }
				    }
                    std::cout << "g - go back\n";

                    std::cout << '\n';
                    std::cout << "Use which item? \n";
                    std::cout << '\n';

                    std::cin >> userInput;
                       
                    if (std::find(usableItems.begin(), usableItems.end(), userInput) != usableItems.end()) {

                        if (userInput == "Vitality-Potion") {
                            

                            if (player.getHealthPoints() == player.getMaxHealth())
                                std::cout << "You are already at full health...";
                            else {
                                turnsLeft--;
                                int healAmount = getRand(4, 10);
                                player.getItem("Vitality-Potion").amount--;
                                player.heal(healAmount);
                                std::cout << "You have healed for " << healAmount << " health points...\n";
                            }

                            std::cout << '\n';

                            std::cout << "Type \"Enter\" to continue...\n";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cin.get();

                        }

                        else if (userInput == "Smokebomb") {
                            player.getItem("Smokebomb").amount--;
                            ran = true;
                            std::cout << "You use a smokebomb to escape...\n";
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                            std::cout << "You have successfully ran away...\n";
                            
                            break;
                        }

                        else if (userInput == "Throwing-Knives") {
							turnsLeft--;
                            enemiesFell++;

                            player.getItem("Throwing-Knives").amount--;

							int randomEnemy = getRand(0, (int)enemiesToFight.size() - 1);

                            enemiesToFight[randomEnemy].setHealthPoints(0);

                            std::cout << "You throw knives and kill the " << enemiesToFight[randomEnemy].getName() << "...\n";
                            std::this_thread::sleep_for(std::chrono::milliseconds(2500));

                            enemiesToFight.erase(enemiesToFight.begin() + randomEnemy);

                            std::cout << '\n';

						}

                    }
                    else if (userInput == "g") {
                        clearScreen();
                        continue;
                    }
                    else {
                        std::cout << '\n';
                        std::cout << "Invalid item. Please try again...\n";
						std::cout << "Type \"Enter\" to continue...\n";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cin.get();

						clearScreen();
						drawEnemies(enemiesToFight);
						std::cout << "Current Health: " << player.getHealthPoints() << '\n';

						goto itemChoice;
                    }
            }   

        }
        else {
            std::cout << '\n';
            std::cout << "Invalid option. Please try again...\n";
            std::cout << "Type \"Enter\" to continue...\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }

        std::cout << '\n';

        if (turnsLeft == 0) {

            turnsLeft = 2;

            for (auto& enemy : enemiesToFight) {
                if (enemy.getHealthPoints() > 0) {

                    //The enemy's damage is randomized from 1 to their damage attribute
                    int enemyDamage = getRand(1, enemy.getMaxDamage());

                    if (enemyDamage > defenseLevel)
                        enemyDamage -= defenseLevel;

                    else if (enemyDamage <= defenseLevel)
                        enemyDamage = 1;
                    
                    player.takeDamage(enemyDamage);
                    std::cout << enemy.getName() << " has attacked you for " << enemyDamage << " damage...\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
            }

        }

        clear:
            clearScreen();

        aliveEnemies = countEnemies(enemiesToFight);

        if (player.getHealthPoints() <= 0) {
            std::cout << "You have been defeated... The game has ended!\n";

            drawDeath();

            std::cout << '\n';

            std::cout << "Type \"Enter\" to exit...\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            exit(0);
        }
        

    }

    if (ran) {
        std::cout << '\n';

        std::cout << "Type \"Enter\" to continue...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        clearScreen();

        return;
    }

    std::cout << "All enemies have been defeated...\n";

    std::vector<std::vector<std::string>> itemsToDraw;

    for (int i = 0; i < enemiesFell;i++) {
        int itemChoice = getRand(0, (int)pickupableItems.size() - 1);

        itemsToDraw.push_back(pickupableItems[itemChoice].image);

		if (pickupableItems[itemChoice].name == "Throwing-Knives")
		    std::cout << "You have found " << pickupableItems[itemChoice].name << "...\n";
        else
			std::cout << "You have found a " << pickupableItems[itemChoice].name << "...\n";

        bool itemFound = false;

		for(auto& item : player.getItems()){
			if (item.name == pickupableItems[itemChoice].name) {
				item.amount++;
                itemFound = true;
				break;
			}
		}

        if (!itemFound) {
            player.addItem(pickupableItems[itemChoice].name, pickupableItems[itemChoice].amount, pickupableItems[itemChoice].damage, pickupableItems[itemChoice].healAmount, pickupableItems[itemChoice].image);
        }

    }

    drawItems(itemsToDraw);

    std::cout << '\n';
    std::cout << "Type \"Enter\" to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();


    clearScreen();


}

void drawItems(std::vector<std::vector<std::string>>& itemsToDraw) {

    for (int i = 0; i < itemsToDraw[0].size(); i++) {
        std::string push = "";
        for(int j = 0;j < itemsToDraw.size();j++)
            push += itemsToDraw[j][i];
        std::cout << push << '\n';
    }
}

int countEnemies(std::vector<Enemy>& enemiesToFightIn) {
    int count{};

    for (int i = 0; i < enemiesToFightIn.size(); i++) {
        if (enemiesToFightIn[i].getHealthPoints() > 0) {
            count++;
        }
    }

    return count;
}

void drawEnemies(std::vector<Enemy> &enemiesToFight) {
    
    for (int i = 0; i < dungeon.size() * 2; i++) {
        std::cout << "-";
    }

    std::cout << '\n';

    std::vector<std::string> enemyArt;

    for (int i = 0; i < enemiesToFight[0].getImage().size(); i++) {
        std::string push = "";
        for (int j = 0; j < enemiesToFight.size(); j++) {
            push += enemiesToFight[j].getImage()[i];
        }
        enemyArt.push_back(push);
    }

	for (int i = 0; i < enemyArt.size(); i++) {
		std::cout << enemyArt[i] << '\n';
	}

    //printing the enemies names and health values
    for(int i = 0; i < enemiesToFight.size(); i++) {
        if (enemiesToFight[i].getHealthPoints() > 0)
            
            std::cout << '\n';

		    std::cout << enemiesToFight[i].getName() << " - " << enemiesToFight[i].getHealthPoints() << "     ";
	}

    std::cout << '\n';

    for (int i = 0; i < dungeon.size() * 2; i++) {
        std::cout << "-";
    }

    std::cout << '\n';

}

std::vector<int> playerStart() {

    std::vector<int> playerPostion;

    //finding the
    for (int i = 0; i < dungeon.size(); i++) {
		for (int j = 0; j < dungeon[i].size(); j++) {
			if (dungeon[i][j] == "s") {
				playerPostion.push_back(i);
				playerPostion.push_back(j);
			}
		}
	}

    return playerPostion;
}

bool eventRoom(std::vector<int> &playerPosition) {
    if(dungeon[playerPosition[0]][playerPosition[1]] == "s" || dungeon[playerPosition[0]][playerPosition[1]] == "w" || dungeon[playerPosition[0]][playerPosition[1]] == "t" || dungeon[playerPosition[0]][playerPosition[1]] == "c" || dungeon[playerPosition[0]][playerPosition[1]] == "b" || dungeon[playerPosition[0]][playerPosition[1]] == "m") {
		return true;
	}
    return false;
}

void inputHandler(std::string& userInput, std::vector<int>& playerPosition, std::vector<bool>& possibleMoves) {

    std::cout << '\n';

    if (userInput == "help") {
        std::cout << "Commands: \n";
        std::cout << "w - move up\n";
        std::cout << "s - move down\n";
        std::cout << "a - move left\n";
        std::cout << "d - move right\n";
        std::cout << "i - inventory\n";
        std::cout << "c - change equipment\n";
        std::cout << "h - heal\n";
        std::cout << "e - exit program\n";

        std::cout << '\n';
        std::cout << "Type \"Enter\" to continue...\n";

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    else if (userInput == "w") {
        if (possibleMoves[0]) {
            playerPosition[0] -= 1;
            player.updateHasBeen(playerPosition[0], playerPosition[1]);
            transition = true;
        }
        else {
            std::cout << "You can't move up right now...\n";
            std::cout << '\n';
            std::cout << "Type \"Enter\" to continue...\n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    else if (userInput == "s") {
        if (possibleMoves[1]) {
            playerPosition[0] += 1;
            player.updateHasBeen(playerPosition[0], playerPosition[1]);
            transition = true;
        }
        else {
            std::cout << "You can't move down right now...\n";
            std::cout << '\n';
            std::cout << "Type \"Enter\" to continue...\n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    else if (userInput == "a") {
        if (possibleMoves[2]) {
            playerPosition[1] -= 1;
            player.updateHasBeen(playerPosition[0], playerPosition[1]);
            transition = true;
        }
        else {
            std::cout << "You can't move left right now...\n";
            std::cout << '\n';
            std::cout << "Type \"Enter\" to continue...\n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    else if (userInput == "d") {
        if (possibleMoves[3]) {
            playerPosition[1] += 1;
            player.updateHasBeen(playerPosition[0], playerPosition[1]);
            transition = true;
        }
        else {
            std::cout << "You can't move right right now...\n";
            std::cout << '\n';
            std::cout << "Type \"Enter\" to continue...\n";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    
    else if (userInput == "i") {

        showInventory();
    }
    else if (userInput == "c") {

        showInventory();

        goto changeE; 

        changeE:
            std::cout << "Change Equipment: \n";

            std::cout << '\n';

            std::cout << "Enter a command to change equipment: \n";
            std::cout << "w - change weapon\n";
            std::cout << "m - change magic\n";
			std::cout << "g - go back\n";
			std::cout << '\n';

			std::cin >> userInput;

            if (userInput == "w") {
                goto weaponE;    
            }
            else if (userInput == "m") {
                goto magicE;
            }
            else if (userInput == "g"){
                goto end;
            }
            else {
                std::cout << "Invalid command. Please try again...\n";

                std::cout << "Type \"Enter\" to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

                clearScreen();
                printDungeon(playerPosition);
                printPlayerStats();

                goto changeE;
            }

        weaponE:
            std::cout << '\n';
            std::cout << "Equip which weapon? \n";
            std::cout << '\n';

            for (auto& weapon : player.getWeapons()) {
                std::cout << weapon.first << '\n';
            }

            std::cout << '\n';

            std::cin >> userInput;

            if (player.getWeapons().find(userInput) != player.getWeapons().end()) {
                player.setCurrentWeapon(userInput);
                std::cout << "You have equipped the " << userInput << "...\n";
                goto end;
            }
            else {
                std::cout << "Invalid weapon. Please try again...\n";
                std::cout << "Type \"Enter\" to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

                clearScreen();
                printDungeon(playerPosition);
                printPlayerStats();

                goto weaponE;
            }

        magicE:
            std::cout << '\n';
            std::cout << "Equip which spell? \n";
            std::cout << '\n';

            for (auto& spell : player.getSpells()) {
                std::cout << spell.first << '\n';
            }

            std::cout << '\n';

            std::cin >> userInput;

            if (player.getSpells().find(userInput) != player.getSpells().end()) {
                player.setCurrentMagic(userInput);
                std::cout << "You have equipped the " << userInput << "...\n";
            }
            else {
                std::cout << "Invalid spell. Please try again...\n";
                std::cout << "Type \"Enter\" to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

                clearScreen();
                printDungeon(playerPosition);
                printPlayerStats();

                goto magicE;
            }

        end:
            std::cout << "Going back to menu...\n";
            std::cout << "Type \"Enter\" to continue...\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
    }
    else if (userInput == "e") {
        std::cout << "Exiting program...\n";
        exit(0);
    }

    else if (userInput == "h") {
        if(player.getHealthPoints() == player.getMaxHealth()) {
			std::cout << "You are already at full health...\n";
		}
		else {
            bool potionFound = false;

            for(auto& item : player.getItems()) {
				if (item.name == "Vitality-Potion") {
                    if (item.amount > 0) {
                        item.amount--;
                        potionFound = true;
                        break;
                    }
				}
			}

            if (potionFound) {
				int healAmount = getRand(4, 10);

				player.heal(healAmount);

				std::cout << "You have healed for " << healAmount << " health...\n";

			}
            else {
                std::cout << "You don't have any Vitality Potions to use...\n";
            }
		}

        std::cout << "Type \"Enter\" to continue...\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();

    }
    else {
        std::cout << "Invalid command. Please try again...\n";
        std::cout << "Type \"Enter\" to continue...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    std::cout << '\n';

}

void showInventory() {

    std::cout << '\n';
    std::cout << "Inventory: \n";

    std::cout << '\n';

    std::cout << "Weapon Dmg Level: " << weaponLevel << '\n';

    std::cout << "Magic Dmg Level: " << magicLevel << '\n';

    std::cout << "Defense Level: " << defenseLevel << '\n';

    std::cout << '\n';

    std::cout << "Equipped Weapon: " << player.getCurrentWeapon() << '\n';

    std::cout << '\n';

    std::cout << "Equipped Magic: " << player.getCurrentMagic() << '\n';

    std::cout << '\n';

    std::cout << "Weapons: \n";
    player.showWeapons();
    
    std::cout << '\n';

    std::cout << "Magic: \n";
    player.showMagic();

    std::cout << '\n';

    std::cout << "Items: \n";
    player.showItems();

    std::cout << '\n';
    std::cout << "Type \"Enter\" to continue...\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

std::vector<bool> moveFinder(std::vector<int> &playerPosition) {

    std::vector<bool> possibleMoves;

    if(playerPosition[0] - 1 >= 0 && dungeon[playerPosition[0] - 1][playerPosition[1]] != "-1" && dungeon[playerPosition[0] - 1][playerPosition[1]] != "0") {
		possibleMoves.push_back(true);
	}
	else {
		possibleMoves.push_back(false);
	}

    if (playerPosition[0] + 1 < dungeon.size() && dungeon[playerPosition[0] + 1][playerPosition[1]] != "-1" && dungeon[playerPosition[0] + 1][playerPosition[1]] != "0") {
        possibleMoves.push_back(true);
    }
    else {
        possibleMoves.push_back(false);
    }

    if (playerPosition[1] - 1 >= 0 && dungeon[playerPosition[0]][playerPosition[1] - 1] != "-1" && dungeon[playerPosition[0]][playerPosition[1] - 1] != "0") {
        possibleMoves.push_back(true);
    }
    else {
		possibleMoves.push_back(false);
	}

    if (playerPosition[1] + 1 < dungeon[0].size() && dungeon[playerPosition[0]][playerPosition[1] + 1] != "-1" && dungeon[playerPosition[0]][playerPosition[1] + 1] != "0") {
		possibleMoves.push_back(true);
	}
	else {
		possibleMoves.push_back(false);
	}

	return possibleMoves;
}

//functional methods
void clearScreen() {
    // Call the system function to execute the "cls" command
    system("cls");
}

void printDungeon(std::vector<int> &playerPosition) {

    for (int i = 0; i < dungeon.size() * 2; i++) {
        std::cout << "-";
    }

	if (player.getHasMap()) {
        for (int i = 0; i < dungeon.size(); i++) {
            for (int j = 0; j < dungeon[i].size(); j++) {
                if (dungeon[i][j] == "-1") {
                    std::cout << "  ";
                }
                else if (i == playerPosition[0] && j == playerPosition[1]) {
                    std::cout << "p ";
                }
                else if (dungeon[i][j] == "1" || dungeon[i][j] == "2" || dungeon[i][j] == "3"){
                    std::cout << "- ";
                }
                else {
                    std::cout << dungeon[i][j] << " ";
                }
            }
            std::cout << '\n';
        }
	}
    else {
        for (int i = 0; i < dungeon.size(); i++) {
            for (int j = 0; j < dungeon[i].size(); j++) {
                if (dungeon[i][j] == "-1") {
                    std::cout << "  ";
                }
				else if (i == playerPosition[0] && j == playerPosition[1]) {
					std::cout << "p ";
				}
                else {
                    if (player.hasBeenSpot(i, j)) {
						if (dungeon[i][j] == "1" || dungeon[i][j] == "2" || dungeon[i][j] == "3")
                            std::cout << "- ";
                        else
							std::cout << dungeon[i][j] << " ";
                    }
                    else {
                        std::cout << "  ";
                    }
                }
            }
            std::cout << '\n';
        }
    }

    for (int i = 0; i < dungeon.size() * 2; i++) {
        std::cout << "-";
    }

    std::cout << '\n';

}