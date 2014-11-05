#include <stdio.h>


/* Farben
 * 0 weiss
 * 1 schwarz
 * 2 gelb
 * 3 blau
 * 4 rot
 * 5 grün
 */

unsigned char tiles[8][6] =
{
    {0,1,2,3,4,5},
    {0,1,5,3,4,2},
    {0,4,5,3,2,1},
    {0,4,5,3,1,2},
    {0,3,1,4,5,2},
    {0,4,5,3,1,2},
    {0,1,4,2,5,3},
    {8,8,8,8,8,8}};

unsigned char positions[7] = {7,7,7,7,7,7,7}; // positionen auf dem Spielfeld, der Wert zeigt an, welches Tile dort liegt
unsigned char rotations[8] = {0,0,0,0,0,0,0,0};
unsigned char available[7] = {1,1,1,1,1,1,1};
unsigned char solutions = 0;

unsigned char d;

unsigned char backtrack(unsigned char pos);
unsigned char valid(unsigned char pos, unsigned char tile, unsigned char rot);
void print_that_solution(void);


int main(void)
{
    positions[0] = 0;
    if(backtrack(0)){
        printf("found\n");
        print_that_solution();
    } else
        printf("done\n");
    return 0;
}

unsigned char backtrack(unsigned char pos)
{
    unsigned char tile = 0;
    unsigned char rot;
    unsigned char nextpos = pos + 1;
    
    // done?
    if(nextpos == 8)
        return 1;
    
    // we're not done yet
    for(tile = 0; tile < 7; tile++){
        if(available[tile]){
            available[tile] = 0;
            for(rot = 0; rot < 6; rot++){
                rotations[pos]= rot;
                if(valid(pos, tile, rot)){
                    //printf("valid\n");
                    positions[pos] = tile;
                    if(backtrack(nextpos)){
                        solutions++;
                        print_that_solution();
                    }
                    positions[pos] = 7;
                }
            }
            rotations[pos] = 0;
            available[tile] = 1;
        }
    }
    return 0;
}


unsigned char valid(unsigned char pos, unsigned char tile, unsigned char rot)
{
    //positions[pos] = tile;
    //print_that_solution();
    //d = getc(stdin);
    //positions[pos] = 7;
    switch (pos) {
        case 0:
            return 1;
            break;
            
        case 1:
            //1.3-0.0
            if(tiles[tile][(3+rot)%6] == tiles[positions[0]][(rotations[0] + 0)%6])
                return 1;
            else
                return 0;
            break;
            
        case 2:
            //2.5-0.2
            if(tiles[tile][(5+rot)%6] == tiles[positions[0]][(rotations[0] + 2)%6])
                return 1;
            else
                return 0;
            break;
            
        case 3:
            //3.4-0.1, 3.5-1.2, 3.3-2.0
            if(tiles[tile][(4+rot)%6] == tiles[positions[0]][(rotations[0] + 1)%6] &&
               tiles[tile][(5+rot)%6] == tiles[positions[1]][(rotations[1] + 2)%6] &&
               tiles[tile][(3+rot)%6] == tiles[positions[2]][(rotations[2] + 0)%6])
                return 1;
            else
                return 0;
            break;
            
        case 4:
            //4.4-1.1, 4.3-3.0
            if(tiles[tile][(4+rot)%6] == tiles[positions[1]][(rotations[1] + 1)%6] &&
               tiles[tile][(3+rot)%6] == tiles[positions[3]][(rotations[3] + 0)%6])
                return 1;
            else
                return 0;
            break;
            
        case 5:
            //5.4-2.1, 5.5-3.2
            if(tiles[tile][(4+rot)%6] == tiles[positions[2]][(rotations[2] + 1)%6] &&
               tiles[tile][(5+rot)%6] == tiles[positions[3]][(rotations[3] + 2)%6])
                return 1;
            else
                return 0;
            break;
            
        case 6:
            //6.4-3.1, 6.3-5.0
            if(tiles[tile][(4+rot)%6] == tiles[positions[3]][(rotations[3] + 1)%6] &&
               tiles[tile][(3+rot)%6] == tiles[positions[5]][(rotations[5] + 0)%6])
                return 1;
            else
                return 0;
            break;
            
        default:
            printf("FATAL: position overflow.\n");
            return 0;
            break;
    }
    
}
/*
void print_that_solution()
{
}*/

void print_that_solution()
{
    printf("Solution %d: \n", solutions);
    printf("%d(%d) %d(%d) %d(%d) %d(%d) %d(%d) %d(%d) %d(%d)\n"
           ,positions[0],rotations[0]
           ,positions[1],rotations[1]
           ,positions[2],rotations[2]
           ,positions[3],rotations[3]
           ,positions[4],rotations[4]
           ,positions[5],rotations[5]
           ,positions[6],rotations[6]);
//    printf("available: %d%d%d%d%d%d%d", available[0],available[1],available[2],available[3],available[4],available[5],available[6]);
    printf("       / \\     / \\       \n");
    printf("      /%d %d\\   /%d %d\\      \n"
           ,tiles[positions[0]][(4+rotations[0])%6]
           ,tiles[positions[0]][(5+rotations[0])%6]
           ,tiles[positions[1]][(4+rotations[1])%6]
           ,tiles[positions[1]][(5+rotations[1])%6]);
    printf("     /     \\ /     \\     \n");
    printf("    |       |       |    \n");
    printf("    |%d  %d  %d|%d  %d  %d|    \n"
           ,tiles[positions[0]][(3+rotations[0])%6]
           ,positions[0]
           ,tiles[positions[0]][(0+rotations[0])%6]
           ,tiles[positions[1]][(3+rotations[1])%6]
           ,positions[1]
           ,tiles[positions[1]][(0+rotations[1])%6]);
    printf("    |       |       |    \n");
    printf("   / \\     / \\     / \\   \n");
    printf("  /%d %d\\%d %d/%d %d\\%d %d/%d %d\\  \n"
           ,tiles[positions[2]][(4+rotations[2])%6]
           ,tiles[positions[2]][(5+rotations[2])%6]
           ,tiles[positions[0]][(2+rotations[0])%6]
           ,tiles[positions[0]][(1+rotations[0])%6]
           ,tiles[positions[3]][(4+rotations[3])%6]
           ,tiles[positions[3]][(5+rotations[3])%6]
           ,tiles[positions[1]][(2+rotations[1])%6]
           ,tiles[positions[1]][(1+rotations[1])%6]
           ,tiles[positions[4]][(4+rotations[4])%6]
           ,tiles[positions[4]][(5+rotations[4])%6]);
    printf(" /     \\ /     \\ /     \\ \n");
    printf("|       |       |       |\n");
    printf("|%d  %d  %d|%d  %d  %d|%d  %d  %d|\n"
           ,tiles[positions[2]][(3+rotations[2])%6]
           ,positions[2]
           ,tiles[positions[2]][(0+rotations[2])%6]
           ,tiles[positions[3]][(3+rotations[3])%6]
           ,positions[3]
           ,tiles[positions[3]][(0+rotations[3])%6]
           ,tiles[positions[4]][(3+rotations[4])%6]
           ,positions[4]
           ,tiles[positions[4]][(0+rotations[4])%6]);
    printf("|       |       |       |\n");
    printf(" \\     / \\     / \\     / \n");
    printf("  \\%d %d/%d %d\\%d %d/%d %d\\%d %d/  \n"
           ,tiles[positions[2]][(2+rotations[2])%6]
           ,tiles[positions[2]][(1+rotations[2])%6]
           ,tiles[positions[5]][(4+rotations[5])%6]
           ,tiles[positions[5]][(5+rotations[5])%6]
           ,tiles[positions[3]][(2+rotations[3])%6]
           ,tiles[positions[3]][(1+rotations[3])%6]
           ,tiles[positions[6]][(4+rotations[6])%6]
           ,tiles[positions[6]][(5+rotations[6])%6]
           ,tiles[positions[4]][(2+rotations[4])%6]
           ,tiles[positions[4]][(1+rotations[4])%6]);
    printf("   \\ /     \\ /     \\ /   \n");
    printf("    |       |       |    \n");
    printf("    |%d  %d  %d|%d  %d  %d|    \n"
           ,tiles[positions[5]][(3+rotations[5])%6]
           ,positions[5]
           ,tiles[positions[5]][(0+rotations[5])%6]
           ,tiles[positions[6]][(3+rotations[6])%6]
           ,positions[6]
           ,tiles[positions[6]][(0+rotations[6])%6]);
    printf("    |       |       |    \n");
    printf("     \\     / \\     /     \n");
    printf("      \\%d %d/   \\%d %d/      \n"
           ,tiles[positions[5]][(2+rotations[5])%6]
           ,tiles[positions[5]][(1+rotations[5])%6]
           ,tiles[positions[6]][(2+rotations[6])%6]
           ,tiles[positions[6]][(1+rotations[6])%6]);
    printf("       \\ /     \\ /       \n");
    printf("\n\n\n");
}

