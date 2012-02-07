#!/bin/env python

from dbfpy import dbf

POP ={
    "CA" : 37691912, "TX" : 25145561, "NY" : 19465197, "FL" : 19057542,
    "IL" : 12869257, "PA" : 12742886, "OH" : 11544951, "MI" : 9876187,
    "GA" : 9815210, "NC" : 9656401, "NJ" : 8821155, "VA" : 8096604,
    "WA" : 6830038, "MA" : 6587536, "IN" : 6516922, "AZ" : 6482505,
    "TN" : 6403353, "MO" : 6010688, "MD" : 5828289, "WI" : 5711767,
    "MN" : 5344861, "CO" : 5116769, "AL" : 4802740, "SC" : 4679230,
    "LA" : 4574836, "KY" : 4369356, "OR" : 3871859, "OK" : 3791508,
    "PR" : 3706690, "CT" : 3580709, "IA" : 3062309, "MS" : 2978512,
    "AK" : 2937979, "KS" : 2871238, "UT" : 2817222, "NV" : 2723322,
    "NM" : 2082224, "WV" : 1855364, "NE" : 1842641, "ID" : 1584985,
    "HI" : 1374810, "ME" : 1328188, "NH" : 1318194, "RI" : 1051302,
    "MT" : 998199, "DE" : 907135, "SD" : 824082, "AR" : 722718,
    "ND" : 683932, "VT" : 626431, "DC" : 617996, "WY" : 568158,
    }

# The backup dbf. We'll need it because we need to
# preserve the state by state order of the rows
# in the new file.
olddb = dbf.Dbf("tl_2010_us_state10-orig.dbf")

# Our new DB file.
newdb = dbf.Dbf("tl_2010_us_state10.dbf", new=True)
newdb.addField(
    ("STATE", "C", 15),
    ("POPULATION", "N", 25, 0),
    )

for rec in olddb:
    # STUSPS10 is the key for the two letter state abbreviation 
    # in the old file.
    abbrev = rec['STUSPS10']

    # Create a new record in our new db file
    # and assign the columns
    rec=newdb.newRecord()
    rec['STATE']=abbrev

    if POP.has_key(abbrev):
        rec['POPULATION']= POP[abbrev]
        pop = POP[abbrev]
    else:
        # Print a message if we cannot find the population
        # for a given record.
        print "BAD POP KEY:", abbrev
        rec['POPULATION']= 0

    rec.store()

olddb.close()
newdb.close()
