//ledmatrix frame
//author: Ismael Salvador
//date: 13/07/2014

led_qty=1;
led_size=60.20;
led_height=60.20;
led_width=led_height*led_qty;
led_depth=9.20;

frame_thick=3;
frame_depth=led_depth+frame_thick*2;
frame_size=led_size + frame_thick;
frame_width=led_width + frame_thick;
frame_height=led_height + frame_thick;

screen_margin=0.2;

angle=15;

difference(){

//outer cube
cube([frame_height, frame_width, frame_depth], center=true);

//inner cube

translate([0,0,frame_thick])
cube([led_height, led_width, frame_depth*1.1], center=true);


//screen hole
//little bit smaller than inner
translate([0,0,-frame_thick])
cube([led_height-screen_margin, led_width-screen_margin, frame_depth*1.1], center=true);

}

stand_depth=frame_depth+6;
stand_height=sin(angle)*stand_depth;

//standoff front
translate([frame_size/2 + stand_height/2, 0, -frame_depth/2 + frame_thick/2 ])
cube([stand_height, frame_width, frame_thick], center=true);

//standoff base
translate([frame_height/2  - 1/2*frame_thick, -frame_width/2, -frame_depth/2])
cube([frame_thick, frame_width, stand_depth], center=false);
//bevel



//translate([0,0,15])
//cube([50,20,2], center=true)
//
//difference(){
//translate([0,20,15])
//cube([30,20,2], center=true);
//
//translate([-10,25,15])
//#cylinder(h = 5, r1 = 1, $fs = 0.1, center = true);
//
//translate([10,25,15])
//#cylinder(h = 5, r1 = 1, $fs = 0.1, center = true);


//}
