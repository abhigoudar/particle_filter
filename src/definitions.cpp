/**Definitions are here*/

#define PI 3.14159265
#define n_particles  1	   // global variable for number of particls
#define displayDelay 1

#define n_laser_meas  187  // length of laser measurements
#define n_odom_meas  4     // lenght of odometry measurements

#define resolution 10

#define angle_max 180
#define angle_min 1
#define inc_srch sqrt(2)
#define detection_threshold 0.9
#define weight_scaling pow(10,0)

#define log_length 2216

#define alpha1 0.00001
#define alpha2 0.00001
#define alpha3 0.00001
#define alpha4 0.00001	

#define laser_offset 25
#define laser_std_dev (1)  // always enter a double value 

string map_file_name="../../data/map/wean.dat";    // location of map.dat file
string log_file_name="../../data/log/robotdata1.log"; // location of log data
string test_log_name="../../data/log/test_log.log"; // test_log 

std::default_random_engine generator1;
std::default_random_engine generator2;
std::default_random_engine generator3;
  
