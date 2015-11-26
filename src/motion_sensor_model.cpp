
mat motion_model(mat particles,mat odom_meas,mat previous_pose)
{
  float delta_x,delta_y,delrot1,delrot2,deltrans;
  delta_x = (odom_meas(0,0) - previous_pose(0,0));
  delta_y = (odom_meas(1,0) - previous_pose(1,0));
  delrot1 = atan2(delta_y,delta_x)- previous_pose(2,0);
  deltrans = sqrt(pow(delta_x,2) + pow(delta_y,2));
  delrot2 = odom_meas(2,0) - previous_pose(2,0) - delrot1;
  std::normal_distribution<double> distribution1(0.0,alpha1*fabs(delrot1)+alpha2*fabs(deltrans));
  std::normal_distribution<double> distribution2(0.0,alpha3*fabs(deltrans) + alpha4*fabs(delrot1+delrot2));
  std::normal_distribution<double> distribution3(0.0,alpha1*fabs(delrot2)+ alpha2*fabs(deltrans));
  cout << delrot1 << " " << distribution1(generator1) << " " << delrot2 << " " << distribution2(generator2) << endl;
  float delcaprot1 = delrot1 - distribution1(generator1);
  float delcaptrans = deltrans - distribution2(generator2);
  float delcaprot2 = delrot2 - distribution3(generator3);
  
  for(int i=0;i<n_particles;i++){
    particles(i,0) = particles(i,0) + delcaptrans * cos(particles(i,2) + delcaprot1);
    particles(i,1) = particles(i,1) + delcaptrans * sin(particles(i,2) + delcaprot1);
    particles(i,2) = particles(i,2) + delcaprot1 + delcaprot2;
  }
  
return particles;
} 

mat sensor_model(mat map,mat particles,mat laser_scan)
{
  double x_loc,y_loc,obs_loc_x,obs_loc_y;
  double theta_rad;
  mat expected_range = zeros<mat>(180,1);
  for (int i=0;i<n_particles;i++)
  {
  x_loc = (particles(i,0)+laser_offset*cos(particles(i,2)))/10; // shift to laser frame
  y_loc = (particles(i,1)+laser_offset*sin(particles(i,2)))/10; // shift to laser frame. 
  
  for(int j=angle_min;j<=angle_max;j++){
  theta_rad = double(j*PI/180);
  obs_loc_x = x_loc;
  obs_loc_y = y_loc;
  while(obs_loc_x >=0 && obs_loc_x<=799 && obs_loc_y >=0 && obs_loc_y<=799){
    if(map(int(obs_loc_y),int(obs_loc_x))>detection_threshold){
	obs_loc_x = obs_loc_x + inc_srch*cos(particles(i,2)+theta_rad);
	obs_loc_y = obs_loc_y + inc_srch*sin(particles(i,2)+theta_rad);
      }
      else {
	expected_range(j-1,0) = sqrt(pow((obs_loc_x-x_loc)*resolution,2)+pow((obs_loc_y-y_loc)*resolution,2));
	break;
      }
    }
  }
  for(int k=angle_min-1;k<angle_max;k++){
   particles(i,3)= particles(i,3) + (1/(laser_std_dev)) *fabs(laser_scan(185-k,0) - expected_range(k,0));
  }
  particles(i,3) = 1/(particles(i,3)) * weight_scaling;
 }
 return particles;
}


