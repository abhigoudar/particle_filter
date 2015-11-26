/** Tool for arma::mat to opencv::mat conversion
 * src is the source arma matrix
 */
void to_cvmat(mat map,mat particles,int j)
{
  cv::Mat_<double> map_image(map.n_rows,map.n_cols,map.memptr());
  map_image = map_image.t();   // to account for the row/col discrepency between opencv and armadillo
  cv::Point center(400,400);
  for(int i=0;i<n_particles;i++) {
   cv::Point center(int(particles(i,0)/resolution),int(particles(i,1)/resolution));
   circle(map_image,center,10.0,cv::Scalar(0.5, 0, 0),-1,8);
  }
  cv::namedWindow("Map", cv::WINDOW_AUTOSIZE );
  cv::imshow("Map", map_image);
  cv::waitKey(displayDelay);
}
