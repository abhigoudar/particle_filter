#include "headers.cpp"
#include "parse_map.cpp"
#include "definitions.cpp"
#include "visualization.cpp"
#include "motion_sensor_model.cpp"
#include "particle_handler.cpp"

int main(int argc,char** argv)
{
   double value;
   bool odom_laser_flag=false;
   string meas,meas_id;
   ifstream log_file;					// input file stream for log file
   istringstream log_stream;				// stream to parse log values
   
   mat laser_meas = zeros<mat>(n_laser_meas,1); 	// vector for laser measure
   mat odom_meas = zeros<mat>(n_odom_meas,1);   	// vector for odom measure
    
   mat map = parse_map(map_file_name);   	        // map in matrix form
   mat particles = initialize_particles(map); 	        // particles as (x,y,p)
   mat previous_pose = zeros<mat>(3,1);
   log_file.open(log_file_name.c_str());
   if(!log_file.is_open()){
    cout<<"log file not open\n";
    return 1;
   }
 // cout << particles << endl;
 for(int j=0;j<=log_length ;j++)
 {
   getline(log_file,meas);
   log_stream.str(meas + " ");
   log_stream >> meas_id;
  if(odom_laser_flag == false){
   if(meas_id == "O"){
     odom_laser_flag = true;
     for(int i=0;i<n_odom_meas;i++){
      log_stream >> value;
      odom_meas(i,0) = value; }
      if(j==1){
      previous_pose(0,0) = odom_meas(0,0);
      previous_pose(1,0) = odom_meas(1,0);
      previous_pose(2,0) = odom_meas(2,0);
      }
      particles=motion_model(particles,odom_meas,previous_pose);
      previous_pose(0,0) = odom_meas(0,0);
      previous_pose(1,0) = odom_meas(1,0);
      previous_pose(2,0) = odom_meas(2,0);
    }
  }
   if(odom_laser_flag == true)
   {  
   if(meas_id == "L"){
     odom_laser_flag = false;
     for(int i=0;i<n_laser_meas;i++){
      log_stream >> value;
      laser_meas(i,0) = value; }
      odom_meas(0,0) = laser_meas(0,0);
      odom_meas(1,0) = laser_meas(1,0);
      odom_meas(2,0) = laser_meas(2,0);
      particles=motion_model(particles,odom_meas,previous_pose);
      particles=sensor_model(map,particles,laser_meas,j);
      previous_pose(0,0) = laser_meas(0,0);
      previous_pose(1,0) = laser_meas(1,0);
      previous_pose(2,0) = laser_meas(2,0);
      particles = resample(particles,j);
    }
   to_cvmat(map,particles,j);
  }
 }
  return 0;
}


