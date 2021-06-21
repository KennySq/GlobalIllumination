#pragma once

class GUIFrame
{
public:
	void Open();
	void Close();

};

class GUIEntity
{
public:

	GUIEntity(GUIFrame* frame);

	void Slider(float& value, float min = 10.0f, float max = 10.0f, const char* label = "Scalar");
	void Slider(int& value, float min = 10.0f, float max = 10.0f, const char* label = "Scalar");
	void Slider(unsigned int& value, float min = 10.0f, float max = 10.0f, const char* label = "Scalar");
	void Slider(double& value, float min = 10.0f, float max = 10.0f, const char* label = "Scalar");

	void Slider(XMFLOAT4& vector, float min = 10.0f, float max = 10.0f, const char* label = "Vector");
	void Slider(XMFLOAT3& vector, float min = 10.0f, float max = 10.0f, const char* label = "Vector");
	void Slider(XMFLOAT2& vector, float min = 10.0f, float max = 10.0f, const char* label = "Vector");

	void Slider(XMFLOAT4X4& matrix, float min = 10.0f, float max = 10.0f, const char* label = "Matrix");
	void Slider(XMFLOAT3X3& matrix, float min = 10.0f, float max = 10.0f, const char* label = "Matrix");

private:
	GUIFrame* mFrame;
};


class GUI
{
public:

	~GUI();

	static GUI* GetInstance(unsigned int width = 0, unsigned int height = 0);

	void Draw();
	void AboutInstance(Instance* inst, float min, float max);

private:
	GUI(unsigned int width, unsigned int height);

	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int mIteration;
	unsigned int mGUICount;

	static GUI* mInstance;
	vector<GUIFrame*> mFrames;
	bool mbOpen;
};

