import processing.serial.*;
import javax.swing.*;

Serial port;

JButton feedButton = new JButton("Feed");

 

ArrayList<Task> tasks = new ArrayList<Task>();

void setup() {
  size(400, 500);
  port = new Serial(this, Serial.list()[1], 9600);
 
  
 
}

void draw() {
  background(#FFFFFF);
  
  if (port.available() > 0) {
    String buffer = port.readString();  
    if (buffer.charAt(0) == '$') {
      readSchedule(buffer.substring(1));
    }
  }
}

void readSchedule(String buffer) {
  String[] subChains = split(buffer, '$');
  for (String subChain : subChains) {
    tasks.add(new Task(subChain.trim()));
  }
}

void keyTyped() {
  if (key == 'p') {
    println("Sending..");
    port.write("P");
  } else if (key == 't') {
    println("Updating time");
    int value = (10000*hour()) + (100*minute()) + second();
    port.write("T"+value);
  }
}
