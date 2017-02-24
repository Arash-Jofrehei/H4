#!/usr/bin/env python
# -*- coding: utf-8 -*-

from collections import OrderedDict

def configure(self):

    self.debug=False # turn on for network messaging debugging
    self.activatesounds=True # turn on to play sounds
    self.sumptuous_browser=True # turn on to use browser tabs for DQM display

    self.pubsocket_bind_address='tcp://*:5566' # address of GUI PUB socket

    self.nodes=[ # addresses of connected nodes
        ('RC','tcp://pcethtb2.cern.ch:6002'),
#        ('RC','tcp://pcminn03.cern.ch:6002'),
#        ('RO1','tcp://pcethtb1.cern.ch:6002'),
        # ('RO2','tcp://cms-h4-03:6002'),
        ('EVTB','tcp://pcethtb2.cern.ch:6502'),
#        ('EVTB','tcp://pcminn03.cern.ch:6502'),
#        ('DRCV1','tcp://localhost:6502'),
        ('DRCV1','tcp://cms-h4-04.cern.ch:6502'),
        ('DRCV2','tcp://cms-h4-05.cern.ch:6502'),
        ('table','tcp://cms-h4-01:6999')
        ]

    self.keepalive={} # nodes to monitor (comment to remove, never put False)
    self.keepalive['RC']=True
 #   self.keepalive['RO1']=True
#    self.keepalive['RO2']=False
    self.keepalive['EVTB']=True
    self.keepalive['DRCV1']=True
    self.keepalive['DRCV2']=True
    self.keepalive['table']=True

    self.temperatureplot=None # 'http://blabla/tempplot.png' to be displayed for temperature history

# DQM plots, to be filled if not using tabbed browsing support
#        self.dqmplots=[] # [('tabname','http://plotname','http://largeplotname.png'),...]
#        self.dqmplots=[
#            ('tab1','/home/cmsdaq/DAQ/H4GUI/plots/canv11.png','/home/cmsdaq/DAQ/H4GUI/plots/canv21.png')
#            ]


    self.scripts={ # scripts linked to GUI buttons
        'sync_clocks': '../H4DAQ/scripts/syncclocks.sh',
        'free_space': None,
#        'start_daemons': '../H4DAQ/scripts/startall.sh -v3 --rc=pcethtb2 --eb=pcethtb2 --dr=pcethtb1',
#        'start_daemons': '../H4DAQ/scripts/startall.sh -v3 --rc=pcethtb1 --eb=pcethtb1 ',
#        'start_daemons': '../H4DAQ/scripts/startall.sh -v3 --rc=pcminn03 --eb=pcminn03 --drcv=localhost --tag=H2_2016_06',
#        'start_daemons': '../H4DAQ/scripts/startall.sh -v3 --rc=pcethtb2 --dr=pcethtb1 --eb=pcethtb2 --drcv=cms-h4-04,cms-h4-05 --drcvrecompile --tag=H4_2016_06',
#       'start_daemons': '../H4DAQ/scripts/startall.sh -v3 --rc=pcethtb2 --eb=pcethtb2 --drcv=cms-h4-04,cms-h4-05 --drcvrecompile --tag=H4_2016_06',
#       'start_daemons': '../H4DAQ/scripts/startall.sh -v3 --rc=pcethtb2 --eb=pcethtb2 --dr=pcethtb1 --drcv=cms-h4-04,cms-h4-05 --drcvrecompile --tag=H4_2016_06_CEF3', #std config for h4
       'start_daemons': '../H4DAQ/scripts/startall.sh -v3 --rc=pcethtb2 --eb=pcethtb2  --drcv=cms-h4-04,cms-h4-05 --drcvrecompile --tag=H4_2016_06_LYSO',
#       'start_daemons': '../H4DAQ/scripts/startall.sh -v3 --rc=pcethtb2 --eb=pcethtb2 --drcv=cms-h4-04,cms-h4-05 --drcvrecompile',
#        'start_daemons': '../H4DAQ/scripts/startall.sh -v3 --rc=pcethtb2 --eb=pcethtb1 --dr=pcethtb1 --drcv=cms-h4-05 --drcvrecompile',
        'kill_daemons': '../H4DAQ/scripts/killall.sh --tag=H4_2016'
        }
    
    self.tableposdictionary = OrderedDict()
    self.tableposdictionary['ZERO']=(0.0,0.0)
    self.tableposdictionary['CEF3_CENTER']=(224.0,294.5)
  #  self.tableposdictionary['CRYSTAL_1']=(190.0,311.5)
  #  self.tableposdictionary['CRYSTAL_2']=(207.0,311.5)
  #  self.tableposdictionary['CRYSTAL_3']=(224.0,311.5)
  #  self.tableposdictionary['CRYSTAL_4']=(241.0,311.5)
  #  self.tableposdictionary['CRYSTAL_5']=(258.0,311.5)
  #  self.tableposdictionary['CRYSTAL_6']=(190.0,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS']=(207.0,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_NE']=(202.7,290.2)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_NW']=(211.2,290.2)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_SE']=(202.7,298.8)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_SW']=(211.2,298.8)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_W']=(215.0,294.5) # 8 mm left
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_3DEG']=(218.9,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_5DEG']=(226.8,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_5DEG_EAST']=(218.8,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_5DEG_WEST']=(234.8,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_5DEG_NORTH']=(226.8,286.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_5DEG_SOUTH']=(226.8,302.5)
  #  self.tableposdictionary['CRYSTAL_11_5DEG']=(243.8,294.5)
  #  self.tableposdictionary['CRYSTAL_11_5DEG_EAST']=(235.8,294.5)
  #  self.tableposdictionary['CRYSTAL_11_5DEG_WEST']=(251.8,294.5)
  #  self.tableposdictionary['CRYSTAL_11_5DEG_NORTH']=(243.8,286.5)
  #  self.tableposdictionary['CRYSTAL_11_5DEG_SOUTH']=(243.8,302.5)
  #
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_7.5DEG']=(236.6,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_10DEG']=(246.4,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_10DEG_EAST']=(238.4,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_10DEG_WEST']=(254.4,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_10DEG_NORTH']=(246.4,286.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_10DEG_SOUTH']=(246.4,302.5)
  #  self.tableposdictionary['CRYSTAL_11_10DEG']=(263.4,294.5)
  #  self.tableposdictionary['CRYSTAL_11_10DEG_EAST']=(255.4,294.5)
  #  self.tableposdictionary['CRYSTAL_11_10DEG_WEST']=(271.4,294.5)
  #  self.tableposdictionary['CRYSTAL_11_10DEG_NORTH']=(263.4,286.5)
  #  self.tableposdictionary['CRYSTAL_11_10DEG_SOUTH']=(263.4,302.5)
  #
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_15DEG']=(265.7,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_15DEG_EAST']=(257.7,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_15DEG_WEST']=(273.7,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_15DEG_NORTH']=(265.7,286.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_15DEG_SOUTH']=(265.7,302.5)
  #
  #  self.tableposdictionary['CRYSTAL_11_15DEG']=(282.7,294.5)
  #  self.tableposdictionary['CRYSTAL_11_15DEG_EAST']=(274.7,294.5)
  #  self.tableposdictionary['CRYSTAL_11_15DEG_WEST']=(300.7,294.5)
  #  self.tableposdictionary['CRYSTAL_11_15DEG_NORTH']=(282.7,286.5)
  #  self.tableposdictionary['CRYSTAL_11_15DEG_SOUTH']=(282.7,302.5)
  #
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_12.5DEG']=(256.1,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_15DEG']=(265.7,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_3DEG_EAST']=(210.9,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_3DEG_WEST']=(226.9,294.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_3DEG_NORTH']=(218.9,286.5)
  #  self.tableposdictionary['CRYSTAL_FOUR_FIBERS_3DEG_SOUTH']=(218.9,302.5)
  #  self.tableposdictionary['CRYSTAL_11_3DEG_EAST']=(227.9,294.5)
  #  self.tableposdictionary['CRYSTAL_11']=(224.0,294.5)
  #  self.tableposdictionary['CRYSTAL_11_3DEG']=(235.9,294.5)
  #  self.tableposdictionary['CRYSTAL_11_5DEG']=(243.8,294.5)
  #  self.tableposdictionary['CRYSTAL_11_7.5DEG']=(253.6,294.5)
  #  self.tableposdictionary['CRYSTAL_11_10DEG']=(263.4,294.5)
  #  self.tableposdictionary['CRYSTAL_11_12.5DEG']=(273.1,294.5)
  #  self.tableposdictionary['CRYSTAL_11_15DEG']=(282.7,294.5)
  #  self.tableposdictionary['CRYSTAL_12']=(241.0,294.5)
  #  self.tableposdictionary['CRYSTAL_13']=(258.0,294.5)
  #  self.tableposdictionary['CRYSTAL_14']=(190.0,277.5)
  #  self.tableposdictionary['CRYSTAL_15']=(207.0,277.5)
  #  self.tableposdictionary['CRYSTAL_16']=(224.0,277.5)
  #  self.tableposdictionary['CRYSTAL_17']=(241.0,277.5)
  #  self.tableposdictionary['CRYSTAL_18']=(258.0,277.5)
  #  self.tableposdictionary['CRYSTAL_11_N']=(224.0,286.5) # 8 mm up
  #  self.tableposdictionary['CRYSTAL_11_S']=(224.0,302.5) # 8 mm down
  #  self.tableposdictionary['CRYSTAL_11_E']=(216.0,294.5) # 8 mm right
  #  self.tableposdictionary['CRYSTAL_11_W']=(232.0,294.5) # 8 mm left

    
    
    otherxtals = OrderedDict() # coordinates seen from the rear face
 #   otherxtals['CAMERONE_1']= (-10.0,-10)
 #   otherxtals['CAMERONE_2']= (+10,-10)
 #   otherxtals['CAMERONE_3']= (-10,+10)
 #   otherxtals['CAMERONE_4']= (+10,+10)

#    otherxtals['BGO_CRY_1']= (-20.0,25.1)
#    otherxtals['BGO_CRY_2']= (2.0,25.0)
#    otherxtals['BGO_CRY_3']= (25.0,22.0)
#    otherxtals['BGO_CRY_4']= (-25.0,2.0)
#    otherxtals['BGO_CRY_5']= (25.0,-2.0)
#    otherxtals['BGO_CRY_6']= (-24.0,-20.0)
#    otherxtals['BGO_CRY_7']= (-2.0,-25.0)
#    otherxtals['BGO_CRY_8']= (21.0,-25.0)
#    otherxtals['BGO_CRY_9']= (-47.0,51.0)
#    otherxtals['BGO_CRY_10']= (-22.0,49.0)
#    otherxtals['BGO_CRY_11']= (2.0,48.0)
#    otherxtals['BGO_CRY_12']= (27.0,45.0)
#    otherxtals['BGO_CRY_13']= (51.0,47.0)
#    otherxtals['BGO_CRY_14']= (-46.0,28.0)
#    otherxtals['BGO_CRY_15']= (50.0,22.0)
#    otherxtals['BGO_CRY_16']= (-50.0,3.0)
#    otherxtals['BGO_CRY_17']= (50.0,0.0)
#    otherxtals['BGO_CRY_18']= (-49.0,-22.0)
#    otherxtals['BGO_CRY_19']= (46.0,-24.0)
#    otherxtals['BGO_CRY_20']= (-49.0,-46.0)
#    otherxtals['BGO_CRY_21']= (-25.0,-45.0)
#    otherxtals['BGO_CRY_22']= (0.0,-49.0)
#    otherxtals['BGO_CRY_23']= (24.0,-49.0)
#    otherxtals['BGO_CRY_24']= (49.0,-49.0)
##
#    otherxtals['CEF3_UP3']= (0.0,15.0)
#    otherxtals['CEF3_UP2']= (0.0,10.0)
#    otherxtals['CEF3_UP1']= (0.0,5.0)
#    otherxtals['CEF3_DOWN1']= (0.0,-5.0)
#    otherxtals['CEF3_DOWN2']= (0.0,-10.0)
#    otherxtals['CEF3_DOWN3']= (0.0,-15.0)
#    
#    otherxtals['CEF3_LEFT3']= (-15.0,0.0)
#    otherxtals['CEF3_LEFT2']= (-10.0,0.0)
#    otherxtals['CEF3_LEFT1']= (-5.0,0.0)
#    otherxtals['CEF3_RIGHT1']= (5.0,0.0)
#    otherxtals['CEF3_RIGHT2']= (10.0,0.0)
#    otherxtals['CEF3_RIGHT3']= (15.0,0.0)
#
#    otherxtals['CEF3_DIAG_SW4']= (-12.0,-12.0)
#    otherxtals['CEF3_DIAG_SW3']= (-9.0,-9.0)
#    otherxtals['CEF3_DIAG_SW2']= (-6.0,-6.0)
#    otherxtals['CEF3_DIAG_SW1']= (-3.0,-3.0)
#    otherxtals['CEF3_DIAG_NE1']= (3.0,3.0)
#    otherxtals['CEF3_DIAG_NE2']= (6.0,6.0)
#    otherxtals['CEF3_DIAG_NE3']= (9.0,9.0)
#    otherxtals['CEF3_DIAG_NE3_CH']= (14.0,13.0)
#    otherxtals['CEF3_DIAG_NE4']= (12.0,12.0)
#
#    otherxtals['CEF3_DIAG_NW4']= (-12.0,12.0)
#    otherxtals['CEF3_DIAG_NW3']= (-9.0,9.0)
#    otherxtals['CEF3_DIAG_NW2']= (-6.0,6.0)
#    otherxtals['CEF3_DIAG_NW1']= (-3.0,3.0)
#    otherxtals['CEF3_DIAG_SE1']= (3.0,-3.0)
#    otherxtals['CEF3_DIAG_SE2']= (6.0,-6.0)
#    otherxtals['CEF3_DIAG_SE3']= (9.0,-9.0)
#    otherxtals['CEF3_DIAG_SE4']= (12.0,-12.0)
##
    for i,j in otherxtals.iteritems():
        self.tableposdictionary[i]=(self.tableposdictionary['CEF3_CENTER'][0]+j[0],self.tableposdictionary['CEF3_CENTER'][1]-j[1])
#        self.tableposdictionary[i]=(self.tableposdictionary['CAMERONE_CENTER'][0]+j[0],self.tableposdictionary['CAMERONE_CENTER'][1]-j[1])
