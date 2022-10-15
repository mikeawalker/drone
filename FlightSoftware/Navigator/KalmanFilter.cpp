#include "KalmanFilter.h"



KalmanFilter::KalmanFilter(int states , int measures )
{
	x = Eigen::VectorXd(16) ;

	y_measure = Eigen::VectorXd::Zero(3);
	y_predict = Eigen::VectorXd::Zero(3);
	y_tilde   = Eigen::VectorXd::Zero(3);

	R = Eigen::MatrixXd::Zero(3,3);
	Q = Eigen::MatrixXd::Zero(16,16);
	S = Eigen::MatrixXd::Zero(3,3);
	STM = Eigen::MatrixXd::Identity(16,16);
	C = Eigen::MatrixXd::Zero(3,16);
	P_predict = Eigen::MatrixXd::Zero(16,16);
	P = Eigen::MatrixXd::Zero(16,16);
	K = Eigen::MatrixXd::Zero(16,3);
	Id = Eigen::MatrixXd::Identity(16,16);
	A = Eigen::MatrixXd::Zero(16,16);
}

KalmanFilter::~KalmanFilter()
{

}




void KalmanFilter::KalmanUpdate()
{
	y_tilde = y_measure - y_predict;
	S = C*P_predict*C.transpose() + R;
	K = P_predict*C.transpose()*S.inverse();
	x = x + K*y_tilde;
}


void KalmanFilter::KalmanTimeUpdate()
{
	double dt = currTime_ - lastTime_;
	dSTM = Eigen::MatrixXd(16,16);
	STM = Eigen::MatrixXd::Identity(16,16);
	dSTM=  A*STM;
	STM = STM+(dSTM)*dt;
	P_predict =  STM*P*STM.transpose()  + Q;


}