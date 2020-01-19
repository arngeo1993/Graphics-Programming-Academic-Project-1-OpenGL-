
#ifndef FRC_H
#define FRC_H
class FrameRateController
{
public:
	FrameRateController(unsigned int MaxFrameRate);
	~FrameRateController();

	void FrameStart();
	void FrameEnd();

	double GetFrameTime();

private:
	double mTickStart;
	double mTickEnd;
	double mFrameTime;
	double mNeededTicksPerFrame;
};

#endif