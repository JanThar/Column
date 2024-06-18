top = 1; // different top pieces 0-6
printParts = false; // lay out 3D-printed parts
showMirror = true;
showGrid = false;
showSocket = true;

//usbBackInlay(0); // USB Backside
usbMale(0); //double USB A socket
//translate([0,0,750+22+3]) columnPower();
//columnStabilizer(); // stabilaizer for frame, use projection(cut=false) before for lasercut version
//translate([0,0,12])columnCapitel();


// optional
//columnConnector(); // screw columns on walls instead of standing on ground
//columnCapitel1(); // alternative top for column


//just for checks
//translate([0,0,750+14]) column(); // simulate column with hull
//for(i=[0:2])                      // simulate frames
//    rotate([0,0,120*i]) 
//    translate([0,81.461-6,750/2]) 
//    cube([11.5,11.5,750],true); //19.5

module usbMale(holes) {
    difference() {
        union() {
            hull() for(i=[-1,1]) for(j=[-1,1]) 
                translate([(31-5)/2*i,(26-5)/2*j,0])
                cylinder(d=5,h=5,$fn=18);
            //translate([0,0,-10])cylinder(d=23.5,h=10);
            translate([0,0,5])cylinder(d=23.5,h=4);//h 2.5
        }
        for(i=[-1,1])
            translate([24/2*i,19/2*i,0]) 
            cylinder(d=4,h=30,$fn=36,center=true);
//        for(i=[-1,1])
//            translate([0,i*5,-12]) cube([14.5,6.5,100],true);
        for(i=[-1,1])
            translate([i*5,0,0]) 
            hull() {
                translate([0,0,0]) cube([6.8,14.4,30],true);
                
                //translate([0,0,-10]) cube([7,14.5,20],true);
            }
    }
    if (holes==1)
        for(i=[-1,1])
        translate([24/2*i,19/2*i,0]) 
        cylinder(d=3.4,h=30,$fn=36,center=true);
}

module columnConnector() {
    difference() {
        union() {
            intersection() {
                hull() for(i=[0:1]) {
                    rotate([0,0,120*i+30]) 
                        translate([0,81.461-6,-50/2]) 
                        cube([11.5,11.5,50],true); //19.5
                }
                hull() {
                    translate([0,0,-6])
                        cube([150,150,12],true);
                    translate([0,0,-12.5])
                        cube([200,50,25],true);
                }

            }
        }
        for(i=[0:2]) 
            rotate([0,0,120*i+30]) 
            translate([0,81.461-6,-11.5/2]) 
            cylinder(d=5.5,h=100,$fn=36,center=true);
        for(i=[0:2]) 
            rotate([0,0,120*i+30]) 
            translate([0,81.461-6,-100-12]) 
            cylinder(d=9,h=100,$fn=36);
        translate([0,0,-12.5])
            rotate([0,90,0]) 
            cylinder(d=14,h=100,center=true);
        for(i=[-1,1])
            translate([0,25*i,-12.5])
                hull() {
                    translate([0,0,-2])
                        rotate([0,90,0]) 
                        cylinder(d=2,h=100,center=true);
                    translate([0,0,2])
                        rotate([0,90,0]) 
                        cylinder(d=2,h=100,center=true);
                }
    }
}

module usbBackInlay (holes) {
    difference() {
        union() {
            hull() for(i=[-1,1]) for(j=[-1,1]) 
                translate([(31-5)/2*i,(26-5)/2*j,0])
                cylinder(d=5,h=2,$fn=18);
            translate([0,0,-8])cylinder(d=22,h=8);
            //translate([0,0,2])cylinder(d=23.5,h=2.5);
        }
        
        for(i=[-1,1]) for(j=[-1,1])
            translate([10*i,3.5*j,0]) 
            cylinder(d=4,h=30,$fn=36,center=true);
        
        for(j=[-1,1])
            translate([0,3.5*j,-10]) 
            cube([400,4,10],true);
        
        for(i=[-1,1]) //for(j=[-1,1])
            translate([24/2*i,-19/2*i,0]) 
            cylinder(d=3.4,h=30,$fn=36,center=true);
//        translate([0,0,3]) cube([14.5,6.5,8],true);
//        hull() {
//            translate([0,0,-9]) cube([14.5,6.5,20],true);
//            translate([0,0,-11]) cube([20,10.5,20],true);
//        }
    }
    if (holes==1)
        for(i=[-1,1]) //for(j=[-1,1])
        translate([24/2*i,19/2*i,0]) 
        cylinder(d=3.4,h=30,$fn=36,center=true);
}
module columnCapitel() {
    difference() {
        union() {
            hull() {
                for(i=[0:2]) 
                    rotate([0,0,120*i]) 
                    translate([0,81.461-6,-5+1]) 
                    cube([11.5+8.5,11.5+8.5,14],true); //19.5
            
            }
//            for(i=[0:2]) hull() {
//                translate([0,0,60]) rotate([0,0,30]) cylinder(d=15,h=1,$fn=3);
//                rotate([0,0,120*i]) 
//                    translate([0,81.461-6+2,3]) 
//                    cube([11.5,11.5,1],true); //19.5
//            }
        }
        for(i=[0:2]) 
            rotate([0,0,120*i]) 
            translate([0,81.461-6,-11]) 
            cylinder(d=5.5,h=100,center=true,$fn=36);
        for(i=[0:2]) 
            rotate([0,0,120*i]) 
            translate([0,81.461-6,13-5]) 
            cylinder(d=10,h=20,center=true,$fn=36);
        difference() {
            hull() for(i=[0:2]) 
                rotate([0,0,120*i]) 
                translate([0,81.461-6,-5-4]) 
                cube([11.5+5.5,11.5+5.5,16],true); //27.5
            hull() for(i=[0:2]) 
                rotate([0,0,120*i]) 
                translate([0,81.461-6,-5-4]) 
                cube([11.5,11.5,16],true); //27.5
        }
        
        hull() for(i=[0:2]) rotate([0,0,120*i]) translate([0,81.461-6-15,-4]) cylinder(d=15,h=14, center=true);
    }
}

module columnCapitel1() {
    difference() {
        union() {
            translate([0,0,-121.67])
                rotate([0,0,30])
                cylinder(d=13.3,h=11.5,$fn=3);
            difference() {
                hull() for(i=[0:2]) 
                    rotate([0,0,120*i]) 
                    translate([0,81.461-6,-11.5/2]) 
                    cube([11.5,11.5,11.5],true); //19.5
                hull() for(i=[0:2]) 
                    rotate([0,0,120*i]) 
                    translate([0,81.461-6-11.5-2,-11.5/2]) 
                    cube([0.5,11.5,20],true); //19.5
            }
            //rotate([0,180,0])
            for(i=[0:2]) 
                translate([0,0,-11.5])
                rotate([0,0,120*i]) 
                translate([0,81.461-6+11.5/2,0]) 
                rotate([-35.26,0,0])
                translate([0,-11.5/2,-134.912/2]) 
    cube([11.5,11.5,134.912],true);
        }

        for(i=[0:2]) 
            rotate([0,0,120*i]) 
            translate([0,81.461-6,-11.5/2]) 
            cylinder(d=5.5,h=100,$fn=36,center=true);
        
        for(i=[0:2]) 
            rotate([0,0,120*i]) 
            translate([0,81.461-6,-18]) 
            cylinder(d=8,h=20,$fn=36,center=true);
    }
}

module columnPower() {  
    reduceHeight = 2;
    difference() {
        hull() for(i=[0:2]) 
            rotate([0,0,120*i]) 
            translate([0,81.461-6,-11+reduceHeight/2]) 
            cube([11.5+8.5,11.5+8.5,38-3-reduceHeight],true);
        for(i=[0:2]) 
            rotate([0,0,120*i]) 
            translate([0,81.461-6,-11]) 
            cylinder(d=5.5,h=100,center=true);
        for(i=[0:2]) 
            rotate([0,0,120*i]) 
            translate([0,81.461-6,-6.5]) 
            cylinder(d=9.5,h=26,$fn=6,center=true);
        difference() {
            hull() for(i=[0:2]) 
                rotate([0,0,120*i]) 
                translate([0,81.461-6-12,-11+4]) 
                cube([11.5,11.5,38-3],true);
            translate([0,-500,500+2]) cube([1000,1000,1000],true);
            translate([0,0,500+2]) cube([20,1000,1000],true);
        }
        hull() for(i=[0:2]) 
                rotate([0,0,120*i]) 
                translate([0,81.461-6,-11-38+1+4+reduceHeight]) 
                cube([11.5,11.5,38+2],true);
        for(i=[1:2]) 
            translate([0,15,0]) rotate([0,0,120*i]) 
            translate([0,-45.6-6,-11+4]) 
            rotate([90,0,0]) 
            speakonMale(1);
        difference() {
            hull() for(i=[0:2]) 
                rotate([0,0,120*i]) 
                translate([0,81.461-6,-11-4-24+reduceHeight]) 
                cube([11.5+5.5,11.5+5.5,38],true); //27.5
            hull() for(i=[0:2]) 
                rotate([0,0,120*i]) 
                translate([0,81.461-6,-11-4-24+reduceHeight]) 
                cube([11.5,11.5,38],true); //27.5
        }
        hull() {
            translate([-0,-20,-7]) cube([65,59,23],true);
            translate([-0,-17,-10]) cube([65,59,23],true);
        }
        translate([-0,-17,-15]) cube([65,57,23],true);
        
    }
    for(i=[-1,1]) translate([i*54/2,-17,4.5-5]) cylinder(d=6,h=5,$fn=18);
//    for(i=[0:2]) 
//        translate([0,15,0]) rotate([0,0,120*i]) 
//        translate([0,-45.6-6,-11+4]) 
//        rotate([90,0,0]) 
//        speakonMale(1);    
}

module speakonMale(holes) {
    difference() {
        union() {
            hull() for(i=[-1,1]) for(j=[-1,1]) 
                translate([(31-5)/2*i,(26-5)/2*j,0])
                cylinder(d=5,h=4.5,$fn=18);
            translate([0,0,-28.1])cylinder(d=24,h=28.1);
            translate([0,0,4.5])cylinder(d=24,h=2.5);
        }
        for(i=[-1,1]) //for(j=[-1,1])
            translate([24/2*i,19/2*i,0]) 
            cylinder(d=3.4,h=30,$fn=36,center=true);
    }
    if (holes==1)
        for(i=[-1,1]) //for(j=[-1,1])
        translate([24/2*i,19/2*i,0]) 
        cylinder(d=3.4,h=50,$fn=36,center=true);
}
module columnStabilizer() {
    difference() {
        hull() for(i=[0:2]) rotate([0,0,120*i]) translate([0,81.461-6,-11]) cube([11.5,11.5,4],true);
        for(i=[0:2]) rotate([0,0,120*i]) translate([0,81.461-6,-11]) cylinder(d=5.5,h=100,center=true);
        hull() for(i=[0:2]) rotate([0,0,120*i]) translate([0,81.461-6-15,-11]) cylinder(d=15,h=100, center=true);
    }
}

module columnSocket() {
    hull() for(i=[0:3]) rotate([0,0,120*i+30]) translate([0,0,-50+6]) cube([258.653,448,12],true);
    hull() for(i=[0:3]) rotate([0,0,120*i]) translate([0,0,-25]) cube([173.205,100,50],true);
}

module column() {
    hull() for(i=[0:2]) rotate([0,0,120*i]) translate([0,81.461-6,-750/2]) cube([11.5,11.5,750],true);
}


