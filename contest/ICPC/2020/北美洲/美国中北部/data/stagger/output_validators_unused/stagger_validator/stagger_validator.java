import java.util.Date;
import java.io.*;

/** Program to validate team submissions for 'Staggering to the Finish'
 *
 * @author Ed Skochinski
 *
 */
class stagger_validator {
  static final int      ACCEPTED=42;
  static final double   EPSILON=0.005;
  static final int      LINE_LIMIT=100;
  static final int      WRONG_ANSWER=43;

/** Read a line from a BufferedReader, exiting on all Exceptions and Errors.
 *
 */
  static String robustReadLine(BufferedReader r, int lineCount, PrintStream log) {
    String s=null;
    try {
      s=r.readLine();
    }
    catch (Exception ex) {
      log.printf("Exception reading team output near line [%d]\n",lineCount);
      ex.printStackTrace(log);
      log.close();
      System.exit(WRONG_ANSWER);
    }
    catch (Error er) {
      log.printf("Error reading team output near line [%d]\n",lineCount);
      er.printStackTrace(log);
      log.close();
      System.exit(WRONG_ANSWER);
    }
    return s;
  }

  public static void main(String[] args) throws IOException {
    BufferedReader input;
    BufferedReader judgeAnswer;
    String         judgeLine;
    int            judgeLineCount=0;
    boolean        comparisonIsPossible=true;
    int            rc=ACCEPTED;
    BufferedReader stdin;
    String         teamLine;
    int            teamLineCount=0;
    PrintStream    validatorLog;
    
//  for (int i=0; i < args.length; i++) {
//    System.err.printf("%d %s\n",i,args[i]);
//  }

    judgeAnswer=new BufferedReader(new FileReader(args[1]));
    validatorLog=new PrintStream(args[2] + "validator.log");
    validatorLog.printf("Starting validator at %s.\n",new Date().toString());
    validatorLog.printf("  arg[0]='%s' ignored.\n",args[0]);
    validatorLog.printf("  arg[1]='%s' judge answer.\n",args[1]);
    validatorLog.printf("  arg[2]='%s' log dir.\n",args[2]);
    validatorLog.printf("  tolerance=%g.\n",EPSILON);
    stdin=new BufferedReader(new InputStreamReader(System.in));

/*
 *  Reading judge_answer is implicitly error free.  Any exception
 *  raised indicates a fundamental error in the .ans file, rather
 *  than a problem with this code.
 */

    judgeLine=judgeAnswer.readLine(); judgeLineCount= (judgeLine != null) ? judgeLineCount + 1 : judgeLineCount;
    teamLine=robustReadLine(stdin,teamLineCount,validatorLog);
    teamLineCount= (teamLine != null) ? teamLineCount + 1 : teamLineCount;
    comparisonIsPossible= (judgeLine != null) && (teamLine != null);
    while (comparisonIsPossible) {
      String[] judgeToken=judgeLine.split("\\s+",-1);
      double[] judgeValue=null;
      int      jTokens=judgeToken.length;
      String[] teamToken=teamLine.split("\\s+",-1);
      double[] teamValue=null;
      int      thisComparison=ACCEPTED;
      int      tTokens=teamToken.length;

//    compare number of whitespace-delimited tokens first

      if (jTokens != tTokens) {
        validatorLog.printf("j[%d] t[%d] team token length of %d should be %d\n"
                           ,judgeLineCount,teamLineCount,tTokens,jTokens
                           );
        thisComparison=WRONG_ANSWER;
      }

//    attempt to convert tokens to doubles before any comparison attempts

      if (thisComparison == ACCEPTED) {
        judgeValue=new double[jTokens];
        teamValue=new double[jTokens];
        for (int i=0; i < jTokens; i++) {
          judgeValue[i]=Double.parseDouble(judgeToken[i]);  // no error checking necessary for judge_answers
          try {
            teamValue[i]=Double.parseDouble(teamToken[i]);
          }
          catch (Exception e) {
            validatorLog.printf("j[%d] t[%d] unable to convert team token [%d] '%s' to double\n"
                               ,judgeLineCount,teamLineCount,i,teamToken[i]
                               );
            thisComparison=WRONG_ANSWER;
          }
        }
      }

//    compare only if all tokens successfully converted

      if (thisComparison == ACCEPTED) {
        for (int i=0; i < jTokens; i++) {
          if (Math.abs(teamValue[i] - judgeValue[i]) > EPSILON) {
            validatorLog.printf("j[%d] t[%d] team token [%d] value %s exceeds tolerance, should be near %s +/- %f\n"
                               ,judgeLineCount,teamLineCount,i,teamToken[i],judgeToken[i],EPSILON
                               );
            thisComparison=WRONG_ANSWER;
          }
        }
      }

      if (thisComparison != ACCEPTED) {
        rc=WRONG_ANSWER;
      }

      judgeLine=judgeAnswer.readLine(); judgeLineCount= (judgeLine != null) ? judgeLineCount + 1 : judgeLineCount;
      teamLine=robustReadLine(stdin,teamLineCount,validatorLog);
      teamLineCount= (teamLine != null) ? teamLineCount + 1 : teamLineCount;
      comparisonIsPossible= (judgeLine != null) && (teamLine != null);
    }

//  one last check to see if the number of lines in each file are the same

    while (judgeAnswer.readLine() != null) {
      judgeLineCount++;
    }
    while ( (stdin.readLine() != null) && (teamLineCount < LINE_LIMIT) ) {
      teamLineCount++;
    }
    if (judgeLineCount != teamLineCount) {
      validatorLog.printf("judge_answer has %d lines, team_answers has %d lines\n"
                         ,judgeLineCount,teamLineCount
                         );
      rc=WRONG_ANSWER;
    }

    judgeAnswer.close();
    validatorLog.printf("Exiting with return code %d\n",rc);
    validatorLog.flush();
    System.exit(rc);
  }
}
