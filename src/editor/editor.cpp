// This file is part of the Godot Orchestrator project.
//
// Copyright (c) 2023-present Vahera Studios LLC and its contributors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "editor.h"

#include "about_dialog.h"
#include "editor/component_panels/component_panel.h"
#include "editor/component_panels/functions_panel.h"
#include "editor/component_panels/graphs_panel.h"
#include "editor/component_panels/macros_panel.h"
#include "editor/component_panels/signals_panel.h"
#include "editor/component_panels/variables_panel.h"
#include "editor/getting_started.h"
#include "editor/graph/actions/action_menu.h"
#include "editor/graph/actions/default_action_registrar.h"
#include "editor/graph/graph_edit.h"
#include "editor/graph/graph_node.h"
#include "editor/graph/graph_node_pin.h"
#include "editor/graph/graph_node_spawner.h"
#include "editor/graph/nodes/graph_node_comment.h"
#include "editor/graph/nodes/graph_node_default.h"
#include "editor/graph/pins/graph_node_pins.h"
#include "editor/search/search_dialog.h"
#include "editor/search/variable_classification_dialog.h"
#include "editor/updater.h"
#include "editor/window_wrapper.h"
#include "graph/graph_knot.h"
#include "main_view.h"
#include "script_connections.h"
#include "script_view.h"

void register_editor_classes()
{
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorEditorSearchDialogItem);
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorEditorSearchDialog)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorVariableTypeSearchDialog)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorEditorSearchHelpBit)

    // Action components
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphActionDB)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphActionMenu)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphActionMenuItem)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphActionHandler)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawner)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphActionRegistrar)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorDefaultGraphActionRegistrar)

    // Node spawners
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerProperty)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerPropertyGet)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerPropertySet)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerCallMemberFunction)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerCallScriptFunction)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerEvent)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerEmitMemberSignal)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerEmitSignal)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerVariable)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerVariableGet)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerVariableSet)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeSpawnerScriptNode)

    // View components
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorUpdater)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorAboutDialog)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorScreenSelect)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorWindowWrapper)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorMainView)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGettingStarted)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorScriptConnectionsDialog)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorScriptView)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorScriptComponentPanel)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorScriptFunctionsComponentPanel)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorScriptGraphsComponentPanel)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorScriptMacrosComponentPanel)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorScriptSignalsComponentPanel)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorScriptVariablesComponentPanel)

    // Graph Classes
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphEdit)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNode)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePin)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorKnotPoint)

    // Graph Node Type
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeDefault)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodeComment)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphKnot)

    // Pin Helpers
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorSceneTreeDialog)

    // Graph Pin Types
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinBitField)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinBool)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinColor)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinEnum)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinExec)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinFile)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinNodePath)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinNumeric)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinObject)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinString)
    ORCHESTRATOR_REGISTER_INTERNAL_CLASS(OrchestratorGraphNodePinStruct)

}