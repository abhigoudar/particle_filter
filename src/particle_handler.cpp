mat initialize_particles(mat map)
{
 std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0,2*PI);

 mat possible_locations = zeros<mat>(800*800,2);
 int k=0;
 for(int i=1;i<800;i++)
 {
   for(int j=1;j<800;j++)
   {
     if(map(j,i)>0.9){
       possible_locations(k,0)=j;
       possible_locations(k,1)=i;
       k=k+1;
     }
   }
 } 
 mat indices = randi<mat>(n_particles,1,distr_param(1,k));
 mat particles = zeros<mat>(n_particles,4);
 for (int i=0;i<n_particles;i++)
 {
  particles(i,0) = resolution * possible_locations(indices(i,0),1);  // x coordinates
  particles(i,1) = resolution * possible_locations(indices(i,0),0);  // y coordinates
  //particles(i,2) = distribution(generator);
 } 
 //cout << particles.col(2) << endl;
 //particles.col(0) = 171 * resolution;
 //particles.col(1) = 284 * resolution;
 particles.col(2) = randu<mat>(n_particles,1)*2*PI;		     // thetas
 particles.col(3) = ones<mat>(n_particles,1);                        // weights
 return particles;
}

mat resample(mat particles,int j)
{
  float ratio=5;;
  if(j < 500)
  ratio =40.0;
  if(j>500 && j<1000)
  ratio = 35.0;
  if(j>1000 && j<1500)
  ratio=20;
  if(j > 1500)
  ratio=1;
  cout << j << " " << ratio << endl;
  mat weights=zeros<mat>(n_particles,1);
  weights = particles.col(3);
  
  if((weights.max()/weights.min())>=ratio){
  uvec index;
  double rand_num;
  particles.col(3) = particles.col(3)/sum(particles.col(3));
  mat cum_sum_weights = cumsum(particles.col(3));
  for(int i=0;i<n_particles;i++){ 
   rand_num = double(rand())/RAND_MAX;
   index = find(cum_sum_weights >= rand_num);
   particles.row(i) = particles.row(index(0));
  }
 }
  particles.col(3) = ones<mat>(n_particles,1);
  return particles;
}
