cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET( appName EthernetDrone )




include_directories( Autopilot ) 
include_directories( Guidance ) 
include_directories( Navigator) 
include_directories( Device ) 
include_directories( HiveMind ) 
include_directories( Messages ) 
include_directories( Tools ) 
include_directories( Include )



link_directories( BOOST_ROOT ) 