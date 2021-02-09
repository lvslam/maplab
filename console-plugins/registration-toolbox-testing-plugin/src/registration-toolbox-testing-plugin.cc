#include "registration-toolbox-testing-plugin/registration-toolbox-testing-plugin.h"

#include <aslam/common/timer.h>
#include <console-common/console.h>
#include <map-manager/map-manager.h>
#include <posegraph/pose-graph.h>
#include <posegraph/unique-id.h>
#include <vi-map/vi-map-serialization.h>
#include <vi-map/vi-map.h>
#include <visualization/viwls-graph-plotter.h>

#include "dense-mapping/dense-mapping.h"
#include "registration-toolbox-testing-plugin/test-registration-toolbox.h"

DECLARE_string(map_mission);

namespace registration_toolbox_testing {

RegistrationToolboxTestingPlugin::RegistrationToolboxTestingPlugin(
    common::Console* console, visualization::ViwlsGraphRvizPlotter* plotter)
    : common::ConsolePluginBaseWithPlotter(console, plotter) {
  CHECK_NOTNULL(console);
  addCommand(
      {"trtb", "test_registration_toolbox"},
      [this]() -> int { return testRegistrationToolbox(); },
      "Add dense mapping constaints to map based on the attached dense sensor "
      "data, such as point clouds. Depending on the configuration "
      "this will add 6DoF constraints within or across missions using a "
      "configurable dense map alignment algorithm, such as ICP.",
      common::Processing::Sync);
}

int RegistrationToolboxTestingPlugin::testRegistrationToolbox() const {
  std::string selected_map_key;
  if (!getSelectedMapKeyIfSet(&selected_map_key)) {
    return common::kStupidUserError;
  }
  vi_map::VIMapManager map_manager;
  vi_map::VIMapManager::MapWriteAccess map =
      map_manager.getMapWriteAccess(selected_map_key);

  // Select mission(s).
  vi_map::MissionIdList mission_ids;
  if (!FLAGS_map_mission.empty()) {
    if (!FLAGS_map_mission_list.empty()) {
      LOG(ERROR) << "Please provide only one of --map_mission and "
                 << "--map_mission_list.";
      return common::kStupidUserError;
    }
    vi_map::MissionId mission_id;
    if (!map->hexStringToMissionIdIfValid(FLAGS_map_mission, &mission_id)) {
      LOG(ERROR) << "The given mission id \"" << FLAGS_map_mission
                 << "\" is not valid.";
      return common::kStupidUserError;
    }
    mission_ids.emplace_back(mission_id);
  } else if (!FLAGS_map_mission_list.empty()) {
    if (!vi_map::csvIdStringToIdList(FLAGS_map_mission_list, &mission_ids)) {
      LOG(ERROR) << "The provided CSV mission id list is not valid!";
      return common::kStupidUserError;
    }
  } else {
    map->getAllMissionIds(&mission_ids);
  }

  if (mission_ids.empty()) {
    LOG(ERROR) << "No missions found to process.";
    return common::kStupidUserError;
  }

  timing::TimerImpl timer("test_registration_toolbox");
  if (!testRegistrationToolboxWithMap(mission_ids, map.get())) {
    LOG(ERROR) << "Failed to test registration toolbox.";
    return common::kStupidUserError;
  }
  timer.Stop();

  LOG(INFO) << timing::Timing::Print();

  return common::kSuccess;
}

}  // namespace registration_toolbox_testing

MAPLAB_CREATE_CONSOLE_PLUGIN_WITH_PLOTTER(
    registration_toolbox_testing::RegistrationToolboxTestingPlugin);
