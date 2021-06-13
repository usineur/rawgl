#include <imgui_vita.h>
#include <psp2/appmgr.h>
#include <stdio.h>
#include <vitaGL.h>
#include <vitasdk.h>

#define VERSIONS 3

const char *PATHS[VERSIONS] = {
	"ux0:data/rawgl/dos",
	"ux0:data/rawgl/3do",
	"ux0:data/rawgl/3do/OutOfThisWorld.iso"
};
const char *FILES[VERSIONS] = {
	"ux0:data/rawgl/dos/memlist.bin",
	"ux0:data/rawgl/3do/GameData/File1",
	"ux0:data/rawgl/3do/OutOfThisWorld.iso"
};
const char *DESCS[VERSIONS] = {
	"Launch DOS version",
	"Launch 3DO version",
	"Launch 3DO version"
};

int main() {
	bool avail[VERSIONS];
	const char *dataPath = nullptr;
	int i;

	vglInit(0x1000);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplVitaGL_Init();
	ImGui_ImplVitaGL_TouchUsage(true);
	ImGui_ImplVitaGL_UseIndirectFrontTouch(true);
	ImGui_ImplVitaGL_UseRearTouch(false);
	ImGui::StyleColorsDark();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	for (i = 0; i < VERSIONS; i++) {
		SceUID fd = sceIoOpen(FILES[i], SCE_O_RDONLY, 0777);
		avail[i] = fd >= 0;
		sceIoClose(fd);
	}

	for (i = 0; i < VERSIONS; i++) {
		if (avail[i] && !avail[(i + 1) % VERSIONS] && !avail[(i + 2) % VERSIONS]) {
			dataPath = PATHS[i];
			break;
		}
	}

	while (!dataPath) {
		ImGui_ImplVitaGL_NewFrame();

		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Launcher")) {
				for (i = 0; i < VERSIONS; i++) {
					if (ImGui::MenuItem(DESCS[i], nullptr, false, avail[i])) {
						dataPath = PATHS[i];
					}
				}
				if (ImGui::MenuItem("Exit", nullptr, false, true)) {
					dataPath = "";
				}
				ImGui::EndMenu();
			}
			ImGui::SetCursorPosX(870);
			ImGui::EndMainMenuBar();
		}

		ImGui::SetNextWindowPos(ImVec2(0, 19), ImGuiSetCond_Always);
		ImGui::SetNextWindowSize(ImVec2(960, 525), ImGuiSetCond_Always);
		ImGui::Begin("Another World Launcher", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "Welcome to Another World Launcher!");
		ImGui::Text("Select the version to launch");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text("Author: usineur");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "Credits:");
		ImGui::Text("Grégory Montoir - http://cyxdown.free.fr");
		ImGui::Spacing();
		ImGui::Spacing();

		for (i = 0; i < VERSIONS; i++) {
			if (avail[i] && ImGui::Button(DESCS[i])) {
				dataPath = PATHS[i];
			}
		}

		ImGui::End();

		glViewport(0, 0, static_cast<int>(ImGui::GetIO().DisplaySize.x), static_cast<int>(ImGui::GetIO().DisplaySize.y));
		ImGui::Render();
		ImGui_ImplVitaGL_RenderDrawData(ImGui::GetDrawData());
		vglSwapBuffers(GL_FALSE);
	}

	if (dataPath && dataPath != "") {
		char opt1[256];
		snprintf(opt1, sizeof(opt1), "--datapath=%s", dataPath);

		char opt2[256];
		snprintf(opt2, sizeof(opt2), "--render=%s", "software"); // DOS + 3DO

		char *const argv[] = { opt1, opt2, NULL };
		sceAppMgrLoadExec("app0:rawgl.bin", argv, nullptr);
	} else {
		sceKernelExitProcess(0);
	}

	return 0;
}
