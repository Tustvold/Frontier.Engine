#include <Event/FTEventDispatcher.h>
#include <Event/FTEvent.h>
#include <gmock/gmock.h>
#include "TestEventDispatcherTypes.h"
#include <Event/FTEventManager.h>
#include "FTEngine.h"
#include <glfwmock.h>

TEST(TestEventManager, TestRegisterRetrieve) {
    GlfwMock mock;
    FTEngine::setup(true);

    auto manager = FTEngine::getEventManager();
    
    auto dispatcher = manager->getEventDispatcher<MockEventDispatcher>();

    EXPECT_NE(dispatcher.get(), nullptr);

    auto dispatcher2 = manager->getEventDispatcher<MockEventDispatcher>();

    EXPECT_EQ(dispatcher.get(), dispatcher2.get());

    FTEngine::cleanup();
}
