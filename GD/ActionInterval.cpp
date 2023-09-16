#include "ActionInterval.h"

std::shared_ptr<ActionInterval> ActionInterval::create(float duration)
{
	std::shared_ptr<ActionInterval> ptr(new ActionInterval);
	if (ptr->init(duration))
		return ptr;

	return nullptr;
}

bool ActionInterval::init(float duration)
{
	this->duration = duration;
    this->firstTick = false;
	return true;
}

void ActionInterval::step(float dt)
{
    if (firstTick)
    {
        firstTick = false;
        elapsed = 0;
    }
    else
    {
        elapsed += dt;
    }

    float updateDt = std::max(0.0f, std::min(1.0f, elapsed / duration));

    this->update(updateDt);

    done = done ? true : elapsed >= duration;
}

void ActionInterval::stepNoUpdate(float dt)
{
    if (firstTick)
    {
        firstTick = false;
        elapsed = 0;
    }
    else
    {
        elapsed += dt;
    }

    done = done ? true : elapsed >= duration;
}

void ActionInterval::update(float time)
{
	//std::cout << "Override me! " << time << " " << elapsed << std::endl;
}