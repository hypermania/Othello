#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "state.h"
#include "io.h"
#include "genconf.h"
#include "game.h"
#include "test.h"

#define BUFF_SIZE 256

int main(int argc, char **argv){
  // set up random number generator
  struct timeval t;
  gettimeofday(&t, NULL);
  //srand((long int) t.tv_usec);
  srand((long int) 100);

  int total_match = 0;
  
  char buff[BUFF_SIZE];
  memset(buff, 0, BUFF_SIZE);
   
  FILE *fp;
  fp = fopen("./game_base/all_games.txt", "r");
  State state = create_state();
  int i;
  
  while(!feof(fp)){
    fgets(buff, BUFF_SIZE, fp);
    Pos *seq = file_to_seq(buff, BUFF_SIZE);
    
    
    Config boards = create_and_init_config_list(100);
    Config config = create_and_init_config();
    init_state(state);
    int turns = genconf_from_seq(state, seq, boards);
    if(turns > 0){
      
      config->w = 0x00000000000000ff;
      int matches = match_conf(boards, config, turns);
      total_match += matches;
    }
    
  }
  printf("total = %d\n", total_match);
  printf("percentage = %lf\n", (double)total_match/(111000*60));
  
  free_state(state);

  
  // run tests
  /*
  printf("test_board = %d\n", test_board());
  printf("test_state = %d\n", test_state());
  printf("test_table = %d\n", test_table());
  printf("test_genconf = %d\n", test_genconf());
  */

  // run the game
  //run_game(1,1,1,6,6);

  
  exit(0);  
}

