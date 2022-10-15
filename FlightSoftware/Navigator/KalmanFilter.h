#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include "Includes.h"

class KalmanFilter
{

public:
	KalmanFilter(int states, int measures);
	~KalmanFilter();
	void Initialize();
	void KalmanUpdate();
	void KalmanTimeUpdate();
	void SetState(double *x);
	
	
private:
	int numStates;
	
	

	void PrintDebug();
	
	

protected:
	Eigen::VectorXd x;

	Eigen::VectorXd y_measure;
	Eigen::VectorXd y_predict;
	Eigen::VectorXd y_tilde;

	Eigen::MatrixXd R;
	Eigen::MatrixXd Q;
	Eigen::MatrixXd S;
	Eigen::MatrixXd STM;
	Eigen::MatrixXd dSTM;
	Eigen::MatrixXd C;
	Eigen::MatrixXd P_predict;
	Eigen::MatrixXd P;
	Eigen::MatrixXd K;
	Eigen::MatrixXd Id;
	Eigen::MatrixXd A;

	double currTime_;
	double lastTime_;
	
};

#endif 