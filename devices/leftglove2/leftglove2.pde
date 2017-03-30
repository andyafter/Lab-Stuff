import processing.serial.*;
import g4p_controls.*;
import java.time.*;

GCustomSlider wave_direction, wave_speed, wave_intensity, slider0, slider1, slider2, slider3, slider4, slider5, slider6, slider7, slider8, slider9, slider10, slider11, slider12, slider13, slider14, slider15, slider16, slider17; 
GButton btnStop, btnSin;
GLabel label_direction, label_speed, label_intensity;

Serial myPort;

int maxNumberOfERMs = 24;
int[] currentValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int rectSize = 33;
PImage bg;
int leftedge_input, leftedge_show;
int f0_x, f0_y, f1_x, f1_y, f2_x, f2_y, f3_x, f3_y, f4_x, f4_y, f5_x, f5_y, f6_x, f6_y, f7_x, f7_y, f8_x, f8_y, f9_x, f9_y, f10_x, f10_y, f11_x, f11_y, f12_x, f12_y, f13_x, f13_y, f14_x, f14_y, f15_x, f15_y, f16_x, f16_y, f17_x, f17_y;
int palm_x, palm_y;
boolean looping = false;
boolean wave = false;
String outString;

long start_time = System.nanoTime();

void setup ()
{
  size(1100, 650);

  leftedge_input = floor(width*0.395);
  leftedge_show = floor(width*0.82);

  // thumb
  f0_x = -floor(width*0.26); 
  f0_y = floor(height*0.4);
  // index finger top
  f1_x = -floor(width*0.183); 
  f1_y = floor(height*0.1);
  // middle finger top
  f2_x = -floor(width*0.105); 
  f2_y = floor(height*0.06);
  // ring finger top
  f3_x = -floor(width*0.040); 
  f3_y = floor(height*0.09);
  // pinky top
  f4_x = floor(width*0.022); 
  f4_y = floor(height*0.22);
  // index finger low
  f5_x = -floor(width*0.168); 
  f5_y = floor(height*0.310);
  // middle finger low
  f6_x = -floor(width*0.111); 
  f6_y = floor(height*0.300);
  // ring finger low
  f7_x = -floor(width*0.055); 
  f7_y = floor(height*0.33);
  // pinky low
  f8_x = -floor(width*0.005); 
  f8_y = floor(height*0.385);
  // palm index finger 
  f9_x = -floor(width*0.16); 
  f9_y = floor(height*0.42);
  // palm middle finger
  f10_x = -floor(width*0.108); 
  f10_y = floor(height*0.40);
  // palm ring finger
  f11_x = -floor(width*0.0595); 
  f11_y = floor(height*0.43);
  // palm pinky
  f12_x = -floor(width*0.0185); 
  f12_y = floor(height*0.46);
  // palm center
  f13_x = -floor(width*0.10); 
  f13_y = floor(height*0.566);
  // palm index low
  f14_x = -floor(width*0.17); 
  f14_y = floor(height*0.615);
  // palm middle low
  f15_x = -floor(width*0.143); 
  f15_y = floor(height*0.69);
  // palm ring low
  f16_x = -floor(width*0.09); 
  f16_y = floor(height*0.715);
  // palm pinky low
  f17_x = -floor(width*0.038); 
  f17_y = floor(height*0.66);

  bg = loadImage("bg2.jpg");
  bg.resize(width, height);

  surface.setTitle("Haptic Glove Control");

  background(255);    // set inital background
  smooth();  // turn on antialiasing
  rectMode(CORNER);
  textSize(20);

  btnStop = new GButton(this, width*0.5, height*0.83, 100, 50);
  btnStop.setText("Stop All");
  btnStop.addEventHandler(this, "stopAll");
  btnStop.setTextBold();
  btnStop.setLocalColorScheme(0);

  btnSin = new GButton(this, width*0.4, height*0.83, 100, 50);
  btnSin.setText("Start Wave");
  btnSin.addEventHandler(this, "sinWave");
  btnSin.setTextBold();
  btnSin.setLocalColorScheme(0);

  label_direction = new GLabel(this, leftedge_input + f9_x, f10_y + 40, 100, 50, "Direction");
  label_direction.setTextBold();
  label_direction.setVisible(false);

  label_intensity = new GLabel(this, leftedge_input + f9_x, f10_y + 90, 100, 50, "Intensity");
  label_intensity.setTextBold();
  label_intensity.setVisible(false);

  label_speed = new GLabel(this, leftedge_input + f9_x, f10_y + 140, 100, 50, "Speed");
  label_speed.setTextBold();
  label_speed.setVisible(false);

  wave_direction = new GCustomSlider(this, leftedge_input + f10_x + 40, f10_y + 40, 50, 50, "red_yellow18px");
  wave_direction.setShowValue(false);
  wave_direction.setLimits(1, -1, 1);
  wave_direction.setStickToTicks(true);
  wave_direction.setNumberFormat(G4P.INTEGER, 0);
  wave_direction.setVisible(false);

  wave_intensity = new GCustomSlider(this, leftedge_input + f10_x + 40, f10_y + 90, 50, 50, "red_yellow18px");
  wave_intensity.setShowValue(true);
  wave_intensity.setLimits(0, 0, 5);
  wave_intensity.setEasing(2.0);
  wave_intensity.setNumberFormat(G4P.INTEGER, 0);
  wave_intensity.setVisible(false);

  wave_speed = new GCustomSlider(this, leftedge_input + f10_x + 40, f10_y + 140, 50, 50, "red_yellow18px");
  wave_speed.setShowValue(true);
  wave_speed.setLimits(0, 0, 5);
  wave_speed.setEasing(2.0);
  wave_speed.setNumberFormat(G4P.INTEGER, 0);
  wave_speed.setVisible(false);

  slider0 = new GCustomSlider(this, leftedge_input + f0_x, f0_y, 50, 50, "red_yellow18px");
  slider0.setShowValue(true);
  slider0.setLimits(0, 0, 5);
  slider0.setEasing(2.0);
  slider0.setNumberFormat(G4P.INTEGER, 0);

  slider1 = new GCustomSlider(this, leftedge_input + f1_x, f1_y, 50, 50, "red_yellow18px");
  slider1.setShowValue(true);
  slider1.setLimits(0, 0, 5);
  slider1.setEasing(2.0);
  slider1.setNumberFormat(G4P.INTEGER, 0);

  slider2 = new GCustomSlider(this, leftedge_input + f2_x, f2_y, 50, 50, "red_yellow18px");
  slider2.setShowValue(true);
  slider2.setLimits(0, 0, 5);
  slider2.setEasing(2.0);
  slider2.setNumberFormat(G4P.INTEGER, 0);

  slider3 = new GCustomSlider(this, leftedge_input + f3_x, f3_y, 50, 50, "red_yellow18px");
  slider3.setShowValue(true);
  slider3.setLimits(0, 0, 5);
  slider3.setEasing(2.0);
  slider3.setNumberFormat(G4P.INTEGER, 0);

  slider4 = new GCustomSlider(this, leftedge_input + f4_x, f4_y, 50, 50, "red_yellow18px");
  slider4.setShowValue(true);
  slider4.setLimits(0, 0, 5);
  slider4.setEasing(2.0);
  slider4.setNumberFormat(G4P.INTEGER, 0);

  slider5 = new GCustomSlider(this, leftedge_input + f5_x, f5_y, 50, 50, "red_yellow18px");
  slider5.setShowValue(true);
  slider5.setLimits(0, 0, 5);
  slider5.setEasing(2.0);
  slider5.setNumberFormat(G4P.INTEGER, 0);

  slider6 = new GCustomSlider(this, leftedge_input + f6_x, f6_y, 50, 50, "red_yellow18px");
  slider6.setShowValue(true);
  slider6.setLimits(0, 0, 5);
  slider6.setEasing(2.0);
  slider6.setNumberFormat(G4P.INTEGER, 0);

  slider7 = new GCustomSlider(this, leftedge_input + f7_x, f7_y, 50, 50, "red_yellow18px");
  slider7.setShowValue(true);
  slider7.setLimits(0, 0, 5);
  slider7.setEasing(2.0);
  slider7.setNumberFormat(G4P.INTEGER, 0);

  slider8 = new GCustomSlider(this, leftedge_input + f8_x, f8_y, 50, 50, "red_yellow18px");
  slider8.setShowValue(true);
  slider8.setLimits(0, 0, 5);
  slider8.setEasing(2.0);
  slider8.setNumberFormat(G4P.INTEGER, 0);

  slider9 = new GCustomSlider(this, leftedge_input + f9_x, f9_y, 50, 50, "red_yellow18px");
  slider9.setShowValue(true);
  slider9.setLimits(0, 0, 5);
  slider9.setEasing(2.0);
  slider9.setNumberFormat(G4P.INTEGER, 0);

  slider10 = new GCustomSlider(this, leftedge_input + f10_x, f10_y, 50, 50, "red_yellow18px");
  slider10.setShowValue(true);
  slider10.setLimits(0, 0, 5);
  slider10.setEasing(2.0);
  slider10.setNumberFormat(G4P.INTEGER, 0);

  slider11 = new GCustomSlider(this, leftedge_input + f11_x, f11_y, 50, 50, "red_yellow18px");
  slider11.setShowValue(true);
  slider11.setLimits(0, 0, 5);
  slider11.setEasing(2.0);
  slider11.setNumberFormat(G4P.INTEGER, 0);

  slider12 = new GCustomSlider(this, leftedge_input + f12_x, f12_y, 50, 50, "red_yellow18px");
  slider12.setShowValue(true);
  slider12.setLimits(0, 0, 5);
  slider12.setEasing(2.0);
  slider12.setNumberFormat(G4P.INTEGER, 0);

  slider13 = new GCustomSlider(this, leftedge_input + f13_x, f13_y, 50, 50, "red_yellow18px");
  slider13.setShowValue(true);
  slider13.setLimits(0, 0, 5);
  slider13.setEasing(2.0);
  slider13.setNumberFormat(G4P.INTEGER, 0);

  slider14 = new GCustomSlider(this, leftedge_input + f14_x, f14_y, 50, 50, "red_yellow18px");
  slider14.setShowValue(true);
  slider14.setLimits(0, 0, 5);
  slider14.setEasing(2.0);
  slider14.setNumberFormat(G4P.INTEGER, 0);

  slider15 = new GCustomSlider(this, leftedge_input + f15_x, f15_y, 50, 50, "red_yellow18px");
  slider15.setShowValue(true);
  slider15.setLimits(0, 0, 5);
  slider15.setEasing(2.0);
  slider15.setNumberFormat(G4P.INTEGER, 0);

  slider16 = new GCustomSlider(this, leftedge_input + f16_x, f16_y, 50, 50, "red_yellow18px");
  slider16.setShowValue(true);
  slider16.setLimits(0, 0, 5);
  slider16.setEasing(2.0);
  slider16.setNumberFormat(G4P.INTEGER, 0);

  slider17 = new GCustomSlider(this, leftedge_input + f17_x, f17_y, 50, 50, "red_yellow18px");
  slider17.setShowValue(true);
  slider17.setLimits(0, 0, 5);
  slider17.setEasing(2.0);
  slider17.setNumberFormat(G4P.INTEGER, 0);

  stroke(0);
  fill(0);
  if (Serial.list().length > 0)
  {
    text("Select serial port for haptic Glove (using keyboard 0-9)", 100, 70);
    for (int i=0; i<Serial.list().length; i++)
    {
      text(i + ": " + Serial.list()[i], 100, 100+30*i);
    }
  } else
  {
    text("No serial ports found. Please make sure device is connected and restart the application.", 100, 70);
  }

  // prevent start until serial port is selected
  noLoop();
}

public void stopAll(GButton source, GEvent event)
{
  for (int i = 0; i < 18; i++)
  {
    currentValues[i] = 0;
  }
  slider0.setValue(0);
  slider1.setValue(0);
  slider2.setValue(0);
  slider3.setValue(0);
  slider4.setValue(0);
  slider5.setValue(0);
  slider6.setValue(0);
  slider7.setValue(0);
  slider8.setValue(0);
  slider9.setValue(0);
  slider10.setValue(0);
  slider11.setValue(0);
  slider12.setValue(0);
  slider13.setValue(0);
  slider14.setValue(0);
  slider15.setValue(0);
  slider16.setValue(0);
  slider17.setValue(0);
}

public void sinWave(GButton source, GEvent event)
{
  if (wave == false)
  {
    btnStop.setEnabled(false);
    btnSin.setText("Stop Wave");
    btnSin.setTextBold();
    for (int i = 0; i < 18; i++)
    {
      currentValues[i] = 0;
    }
    slider0.setVisible(false);
    slider1.setVisible(false);
    slider2.setVisible(false);
    slider3.setVisible(false);
    slider4.setVisible(false);
    slider5.setVisible(false);
    slider6.setVisible(false);
    slider7.setVisible(false);
    slider8.setVisible(false);
    slider9.setVisible(false);
    slider10.setVisible(false);
    slider11.setVisible(false);
    slider12.setVisible(false);
    slider13.setVisible(false);
    slider14.setVisible(false);
    slider15.setVisible(false);
    slider16.setVisible(false);
    slider17.setVisible(false);
    wave_direction.setVisible(true);
    wave_speed.setVisible(true);
    wave_intensity.setVisible(true);
    label_direction.setVisible(true);
    label_intensity.setVisible(true);
    label_speed.setVisible(true);
    wave = true;
  } else {
    btnStop.setEnabled(true);
    btnSin.setText("Start Wave");
    btnSin.setTextBold();
    slider0.setVisible(true);
    slider1.setVisible(true);
    slider2.setVisible(true);
    slider3.setVisible(true);
    slider4.setVisible(true);
    slider5.setVisible(true);
    slider6.setVisible(true);
    slider7.setVisible(true);
    slider8.setVisible(true);
    slider9.setVisible(true);
    slider10.setVisible(true);
    slider11.setVisible(true);
    slider12.setVisible(true);
    slider13.setVisible(true);
    slider14.setVisible(true);
    slider15.setVisible(true);
    slider16.setVisible(true);
    slider17.setVisible(true);
    wave_direction.setVisible(false);
    wave_speed.setVisible(false);
    wave_intensity.setVisible(false);
    label_direction.setVisible(false);
    label_intensity.setVisible(false);
    label_speed.setVisible(false);
    wave = false;
  }
}

void keyPressed()
{  
  int portID = -1;
  println("keypressed: " + key);
  switch(key)
  {
    case('0'): 
    portID = 0; 
    break;
    case('1'): 
    portID = 1;
    break;
    case('2'): 
    portID = 2;
    break;
    case('3'): 
    portID = 3;
    break;
    case('4'): 
    portID = 4;
    break;
    case('5'): 
    portID = 5;
    break;
    case('6'): 
    portID = 6;
    break;
    case('7'): 
    portID = 7;
    break;
    case('8'): 
    portID = 8;
    break;
    case('9'): 
    portID = 9;
    break;
  }

  if (!looping && portID < Serial.list().length && portID >= 0)
  {
    println("starting serial");
    startSerial(portID);
  }
}

void startSerial(int portNumber)
{
  myPort = new Serial(this, Serial.list()[portNumber], 57600);
  myPort.clear();
  myPort.bufferUntil('r');  // don't generate a serialEvent() until you get a newline (r) byte
  looping = true;
  loop();
}

void draw ()
{
  if (looping)
  {
    //int index = 0;
    background(bg);

    if (wave == false)
    {
      currentValues[9] = 20*slider0.getValueI();
      currentValues[12] = 20*slider1.getValueI();
      currentValues[0] = 20*slider2.getValueI();
      currentValues[13] = 20*slider3.getValueI();
      
      currentValues[15] = 20*slider4.getValueI(); //Not working
      currentValues[20] = 20*slider5.getValueI();  //Not working
      currentValues[5] = 20*slider6.getValueI();
      currentValues[6] = 20*slider7.getValueI();
      
      currentValues[16] = 20*slider8.getValueI();
      currentValues[4] = 20*slider9.getValueI();
      currentValues[7] = 20*slider10.getValueI();
      currentValues[8] = 20*slider11.getValueI();
      
      currentValues[17] = 20*slider12.getValueI();
      currentValues[14] = 20*slider13.getValueI(); // Not working
      currentValues[10] = 20*slider14.getValueI();
      currentValues[1] = 20*slider15.getValueI(); //Not working
      
      currentValues[3] = 20*slider16.getValueI();
      currentValues[11] = 20*slider17.getValueI();
    } else {
      double speed = wave_speed.getValueI();
      if (wave_speed.getValueI() >= 1) {
        speed = 1 + (0.5 * wave_speed.getValueI());
      }  
      int direction = wave_direction.getValueI();
      int intensity = wave_intensity.getValueI();   

      long current_time = System.nanoTime();

      double difference = (current_time - start_time)/1e6;
      double phi = 20;

      currentValues[5] = Math.toIntExact(Math.round(Math.sin(Math.toRadians(speed * difference / 5)) * intensity * 20));
      currentValues[8] = Math.toIntExact(Math.round(Math.sin(Math.toRadians((speed * difference / 5) + (direction * phi))) * intensity * 20));
      currentValues[15] = Math.toIntExact(Math.round(Math.sin(Math.toRadians((speed * difference / 5) + (direction * 2 * phi))) * intensity * 20));
      currentValues[17] = Math.toIntExact(Math.round(Math.sin(Math.toRadians((speed * difference / 5) + (direction * 3 * phi))) * intensity * 20));
      currentValues[10] = Math.toIntExact(Math.round(Math.sin(Math.toRadians((speed * difference / 5) + (direction * 4 * phi))) * intensity * 20));
    }
    // thumb
    noStroke();
    fill(255, 0, 0, 2.5*currentValues[9]);
    ellipse(leftedge_show + f0_x + rectSize, f0_y + rectSize, rectSize, rectSize);

    //index top
    fill(255, 0, 0, 2.5*currentValues[12]);
    ellipse(leftedge_show + f1_x + rectSize, f1_y + rectSize, rectSize, rectSize);

    // middle top
    fill(255, 0, 0, 2.5*currentValues[0]);
    ellipse(leftedge_show + f2_x + rectSize, f2_y + rectSize, rectSize, rectSize);

    //ring top
    fill(255, 0, 0, 2.5*currentValues[13]);
    ellipse(leftedge_show + f3_x + rectSize, f3_y + rectSize, rectSize, rectSize);

    //pinky top
    fill(255, 0, 0, 2.5*currentValues[15]);
    ellipse(leftedge_show + f4_x + rectSize, f4_y + rectSize, rectSize, rectSize);

    //index low
    fill(255, 0, 0, 2.5*currentValues[20]);
    ellipse(leftedge_show + f5_x + rectSize, f5_y + rectSize, rectSize, rectSize);

    // middle low
    fill(255, 0, 0, 2.5*currentValues[5]);
    ellipse(leftedge_show + f6_x + rectSize, f6_y + rectSize, rectSize, rectSize);

    //ring low
    fill(255, 0, 0, 2.5*currentValues[6]);
    ellipse(leftedge_show + f7_x + rectSize, f7_y + rectSize, rectSize, rectSize);

    //pinky low
    fill(255, 0, 0, 2.5*currentValues[16]);
    ellipse(leftedge_show + f8_x + rectSize, f8_y + rectSize, rectSize, rectSize);

    //palm index
    fill(255, 0, 0, 2.5*currentValues[4]);
    ellipse(leftedge_show + f9_x + rectSize, f9_y + rectSize, rectSize, rectSize);

    //palm middle
    fill(255, 0, 0, 2.5*currentValues[7]);
    ellipse(leftedge_show + f10_x + rectSize, f10_y + rectSize, rectSize, rectSize);

    //palm ring
    fill(255, 0, 0, 2.5*currentValues[8]);
    ellipse(leftedge_show + f11_x + rectSize, f11_y + rectSize, rectSize, rectSize);

    //palm pinky
    fill(255, 0, 0, 2.5*currentValues[17]);
    ellipse(leftedge_show + f12_x + rectSize, f12_y + rectSize, rectSize, rectSize);

    //palm center
    fill(255, 0, 0, 2.5*currentValues[14]);
    ellipse(leftedge_show + f13_x + rectSize, f13_y + rectSize, rectSize, rectSize);

    //palm index low
    fill(255, 0, 0, 2.5*currentValues[10]);
    ellipse(leftedge_show + f14_x + rectSize, f14_y + rectSize, rectSize, rectSize);

    //palm middle low
    fill(255, 0, 0, 2.5*currentValues[1]);
    ellipse(leftedge_show + f15_x + rectSize, f15_y + rectSize, rectSize, rectSize);

    //palm ring low
    fill(255, 0, 0, 2.5*currentValues[3]);
    ellipse(leftedge_show + f16_x + rectSize, f16_y + rectSize, rectSize, rectSize);

    //palm pinky low
    fill(255, 0, 0, 2.5*currentValues[11]);
    ellipse(leftedge_show + f17_x + rectSize, f17_y + rectSize, rectSize, rectSize);
  }
}

void serialEvent (Serial myPort)
{
  outString = ("r");
  for (int i=0; i<24; i++)
  {
    outString = outString + currentValues[i] + ",";
  }
  myPort.write(outString);
  println("out: " + outString);
  //println("in: " + myPort.read());
}