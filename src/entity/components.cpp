#include <Components.hpp>

const std::string RenderComponent::RENDER_COMP_ID = "RENDER_COMP_ID";
const std::string LocationComponent::LOC_COMP_ID = "LOC_COMP_ID";

RenderComponent::RenderComponent() : Component(RENDER_COMP_ID)
{
}

LocationComponent::LocationComponent() : Component(LOC_COMP_ID)
{
}