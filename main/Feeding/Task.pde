class Task{
  
  int hour = 0,minute = 0,portion = 0;
  boolean given;
  //hhmm
  
  
  Task(String chain){
    //F[0,1]T[0,2359]P[1,20]
    
    int inxP = chain.indexOf("P"); //P index

    given = boolean(int(chain.substring(1,2)));
    int time = int(chain.substring(3,inxP));
    hour = time/100;
    minute = (time - hour*100);
    portion = int(chain.substring(inxP + 1));
  }
  
  String toString(){
    String buffer = "F" + int(given)+"T"+hour+minute+"P"+portion;
    return buffer;
  }
  
}
