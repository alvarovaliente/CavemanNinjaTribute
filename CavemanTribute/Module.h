#ifndef __MODULE_H__
#define __MODULE_H__

class Application;
class Collider;

class Module
{
public:

	Module(bool active = true) : active(active)
	{}

	virtual ~Module()
	{}

	bool IsEnabled() const
	{
		return active;
	}

	bool Enable()
	{
		if (active == false)
			return active = Start();

		return true;
	}

	bool Disable()
	{
		if (active == true)
			return active = !CleanUp();

		return true;
	}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual void OnCollision(Collider* c1, Collider* c2)
	{}

	virtual void OnCollisionEnter(Collider* c1, Collider* c2)
	{}

	virtual void OnCollisionExit(Collider* c1, Collider* c2)
	{}

private:
	bool active = true;
};

#endif // __MODULE_H__