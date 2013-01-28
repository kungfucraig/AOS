#!/usr/bin/python

import math

R = 1
STEP_SIZE=.05
print 'R, "% VOLUME"'
print "******"

TOTAL_AREA=math.pi*R**2
NSTEPS=int(R/STEP_SIZE)
for i in range(1, NSTEPS+1):
    r=i*STEP_SIZE
    area = math.pi*r**2
    print r, area/TOTAL_AREA

print "******"

TOTAL_VOLUME=4.0/3.0*math.pi*R**3
for i in range(1, NSTEPS+1):
    r=i*STEP_SIZE
    vol = 4.0/3.0*math.pi*r**3
    print r, vol/TOTAL_VOLUME



    

    
    


