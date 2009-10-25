######################################################################
# Automatically generated by qmake (2.01a) ?? 24. ??? 16:33:28 2009
######################################################################

TEMPLATE = app
TARGET = Polcovodetz
DEPENDPATH += . \
              Core \
              Internationalization \
              VersionControl \
              Core\BaseClasses \
              Core\Calculations \
              Core\Common \
              Core\Drivers \
              Core\HumanControllers \
              Core\MultiThreading \
              Core\PObjects \
              Core\StateManagers \
              GUI\CommonControls \
              GUI\SpecialControls \
              GUI\TopLevelControls \
              Core\PObjects\Interfaces \
              Core\PObjects\UserObjects \
              Core\PObjects\UserObjects\Flying \
              Core\PObjects\UserObjects\Moving
INCLUDEPATH += .

# Input
HEADERS += Core/LibraryLoader.h \
           Core/PObjectFactory.h \
           Core/PolkApp.h \
           Core/ResourceManager.h \
           Core/ScriptInvoker.h \
           Core/WinState.h \
           VersionControl/SetupDownloader.h \
           VersionControl/VersionInfo.h \
           Core/BaseClasses/AbstractMessage.h \
           Core/BaseClasses/GroupStates.h \
           Core/BaseClasses/IAbstractController.h \
           Core/BaseClasses/IAbstractDrivers.h \
           Core/BaseClasses/ICommandController.h \
           Core/BaseClasses/ICommandDrivers.h \
           Core/BaseClasses/IGroupController.h \
           Core/BaseClasses/IGroupDrivers.h \
           Core/BaseClasses/ILoader.h \
           Core/BaseClasses/IObjectController.h \
           Core/BaseClasses/IObjectDrivers.h \
           Core/BaseClasses/Messages.h \
           Core/Calculations/DriverHelper.h \
           Core/Calculations/MapOperations.h \
           Core/Common/ConcurrentQueue.h \
           Core/Common/DualArray.h \
           Core/Common/GlobalPoint.h \
           Core/Common/Map.h \
           Core/Common/MathUtils.h \
           Core/Common/MovementDirection.h \
           Core/Drivers/SimpleCommandDrivers.h \
           Core/Drivers/SimpleGroupDrivers.h \
           Core/Drivers/SimpleObjectDrivers.h \
           Core/HumanControllers/HumanObjectController.h \
           Core/MultiThreading/CalcThread.h \
           Core/MultiThreading/CommandState.h \
           Core/MultiThreading/CommandThread.h \
           Core/PObjects/PObject.h \
           Core/PObjects/PObjectSharedImpl.h \
           Core/StateManagers/PositionManager.h \
           GUI/CommonControls/CommandControllerChooseForm.h \
           GUI/CommonControls/GroupControllerChooseForm.h \
           GUI/CommonControls/ObjectControllerChooseForm.h \
           GUI/CommonControls/PObjectChooseBox.h \
           GUI/SpecialControls/MapView.h \
           GUI/SpecialControls/PaintArea2D.h \
           GUI/TopLevelControls/CommandTreeForm.h \
           GUI/TopLevelControls/GUIControler.h \
           GUI/TopLevelControls/MainForm.h \
           Core/PObjects/Interfaces/AbstractPObject.h \
           Core/PObjects/Interfaces/IShootableObject.h \
           Core/PObjects/UserObjects/AbstractRocket.h \
           Core/PObjects/UserObjects/Flying/AbstractRocket.h \
           Core/PObjects/UserObjects/Flying/SimpleRocket.h \
           Core/PObjects/UserObjects/Moving/AbstractMoveObject.h \
           Core/PObjects/UserObjects/Moving/SimpleTank.h \
           GUI/SpecialControls/Resources/CommandImage.xpm \
           GUI/SpecialControls/Resources/GroupImage.xpm \
           GUI/SpecialControls/Resources/ObjectImage.xpm \
           GUI/SpecialControls/Resources/Refresh.xpm \
           GUI/SpecialControls/Resources/Map/Empty.xpm \
           GUI/SpecialControls/Resources/Map/Brick.xpm \
           GUI/SpecialControls/Resources/Map/Grassland.xpm \
           GUI/SpecialControls/Resources/Map/Stone.xpm \
           GUI/SpecialControls/Resources/Map/Water.xpm \
           GUI/SpecialControls/Resources/Map/BlueStartPlace.xpm \
           GUI/SpecialControls/Resources/Map/RedStartPlace.xpm \
           GUI/SpecialControls/Resources/Map/BlueFlag.xpm \
           GUI/SpecialControls/Resources/Map/RedFlag.xpm \
           Core/PObjects/Resources/SimpleRocket.xpm \
           Core/PObjects/Resources/BlueSimpleTank.xpm \
           Core/PObjects/Resources/RedSimpleTank.xpm
SOURCES += main.cpp \
           Core/LibraryLoader.cpp \
           Core/PObjectFactory.cpp \
           Core/PolkApp.cpp \
           Core/ResourceManager.cpp \
           Core/ScriptInvoker.cpp \
           Core/WinState.cpp \
           VersionControl/SetupDownloader.cpp \
           VersionControl/VersionInfo.cpp \
           Core/Calculations/DriverHelper.cpp \
           Core/Calculations/MapOperations.cpp \
           Core/Common/ConcurrentQueue.cpp \
           Core/Common/DualArray.cpp \
           Core/Common/GlobalPoint.cpp \
           Core/Common/Map.cpp \
           Core/Common/MathUtils.cpp \
           Core/Common/MovementDirection.cpp \
           Core/Drivers/SimpleCommandDrivers.cpp \
           Core/Drivers/SimpleGroupDrivers.cpp \
           Core/Drivers/SimpleObjectDrivers.cpp \
           Core/HumanControllers/HumanObjectController.cpp \
           Core/MultiThreading/CalcThread.cpp \
           Core/MultiThreading/CommandState.cpp \
           Core/MultiThreading/CommandThread.cpp \
           Core/PObjects/PObject.cpp \
           Core/StateManagers/PositionManager.cpp \
           GUI/CommonControls/CommandControllerChooseForm.cpp \
           GUI/CommonControls/GroupControllerChooseForm.cpp \
           GUI/CommonControls/ObjectControllerChooseForm.cpp \
           GUI/CommonControls/PObjectChooseBox.cpp \
           GUI/SpecialControls/MapView.cpp \
           GUI/SpecialControls/PaintArea2D.cpp \
           GUI/TopLevelControls/CommandTreeForm.cpp \
           GUI/TopLevelControls/GUIControler.cpp \
           GUI/TopLevelControls/MainForm.cpp \
           Core/PObjects/UserObjects/Flying/SimpleRocket.cpp \
           Core/PObjects/UserObjects/Moving/SimpleTank.cpp
TRANSLATIONS += Internationalization/English.ts Internationalization/Russian.ts
