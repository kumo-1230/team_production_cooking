#pragma once

//�V�[��
class Scene
{
private:
	bool ready = false;
protected:
	//���������{�^���̐��l������
	int menuNum = -1;

public:
	Scene() {}
	virtual ~Scene(){}

	//������
	virtual void Initialize() = 0;

	//�I����
	virtual void Finalize() = 0;

	//�X�V����
	virtual void Update(float elapsedTime) = 0;

	//�`�揈��
	virtual void Render() = 0;

	//GUI�`��
	virtual void DrawGUI() = 0;

	//�����������Ă��邩
	bool IsReady() const { return ready; }

	//�����������Ă��邩
	void SetReady() { ready = true; }
};