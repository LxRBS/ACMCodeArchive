// Author Alexander Rass

import java.util.*;

public class AR{

    final static char CHAR_UP = 'U', CHAR_DOWN = 'D', CHAR_LEFT = 'L', CHAR_RIGHT = 'R';
    final static int BOUND = (int)1e9;
    final static int MAX_LENGTH = 1024;
    static void impossible(){
        System.out.println("impossible");
    }
    static void calc(){
        Scanner scan = new Scanner(System.in);
        String input = scan.next();
        scan.close();
        int blocking[][] = new int[MAX_LENGTH][2];
        int B = 0;
        int bound_U = BOUND, bound_L = - BOUND, bound_R = BOUND, bound_D = -BOUND;
        int box_U = 0, box_L = 0, box_R = 0, box_D = 0;
        int UD = 0, LR = 0;
        boolean canfinish = true;
        for(char c: input.toCharArray()){
            canfinish = true;
            switch(c){
                case CHAR_LEFT:
                    if(bound_L == -BOUND){
                        bound_L = (box_L -= 2);
                        blocking[B][0] = bound_L - 1;
                        blocking[B++][1] = UD;
                        bound_U = BOUND; bound_D = -BOUND;
                    } else {
                        canfinish = false;
                    }
                    if(LR == bound_L){
                        impossible();
                        return;
                    }
                    LR = bound_L;
                    break;
                case CHAR_RIGHT:
                    if(bound_R == BOUND){
                        bound_R = (box_R += 2);
                        blocking[B][0] = bound_R + 1;
                        blocking[B++][1] = UD;
                        bound_U = BOUND; bound_D = -BOUND;
                    } else {
                        canfinish = false;
                    }
                    if(LR == bound_R) {
                        impossible();
                        return;
                    }
                    LR = bound_R;
                    break;
                case CHAR_UP:
                    if(bound_U == BOUND){
                        bound_U = (box_U += 2);
                        blocking[B][0] = LR;
                        blocking[B++][1] = bound_U + 1;
                        bound_R = BOUND; bound_L = -BOUND;
                    } else {
                        canfinish = false;
                    }
                    if(UD == bound_U){
                        impossible();
                        return;
                    }
                    UD = bound_U;
                    break;
                case CHAR_DOWN:
                    if(bound_D == -BOUND){
                        bound_D = (box_D -= 2);
                        blocking[B][0] = LR;
                        blocking[B++][1] = bound_D - 1;
                        bound_R = BOUND; bound_L = -BOUND;
                    } else {
                        canfinish = false;
                    }
                    if(UD == bound_D){
                        impossible();
                        return;
                    }
                    UD = bound_D;
                    break;
            }
        }
        if(!canfinish){
            impossible();
            return;
        }
        System.out.println((-LR) + " "+ (-UD));
        System.out.println(B);
        for(int i = 0; i < B; i++){
            System.out.println((blocking[i][0] - LR) + " " + (blocking[i][1] - UD));
        }
    }
    public static void main(String[] args){
        calc();
    }
}
