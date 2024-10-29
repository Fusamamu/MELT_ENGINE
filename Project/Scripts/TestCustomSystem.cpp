#include "TestCustomSystem.h"

TestCustomSystem* CreateCustomSystem()
{
    return new TestCustomSystem();
}

void TestCustomSystem::OnStart()
{

}

void TestCustomSystem::OnInputUpdate(float _dt)
{
    std::cout << "Update Input..." << std::endl;
}

void TestCustomSystem::OnUpdate(float _dt)
{
    std::cout << "Update..." << std::endl;
}

void TestCustomSystem::OnRender(float _dt)
{
    std::cout << "Update Render..." << std::endl;
}

void TestCustomSystem::OnEnd()
{

}
