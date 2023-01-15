#include <App.hpp>

namespace Core
{
	App::~App()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		mRscManager->Clear();
		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
	}

	bool App::Init(AppInitializer& init)
	{
		pybind11::module_ EnginePy = pybind11::module_::import("startup");

		mWidth = init.width; mHeight = init.height;
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, init.major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, init.minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		// glfw Window creation
		// --------------------
		Window = glfwCreateWindow(init.width, init.height, init.name, NULL, NULL);
		if (Window == NULL)
		{
			std::cout << "Failed to create GLFW Window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(Window);
		glfwSetFramebufferSizeCallback(Window, init.framebuffer_size_callback);


		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}


		GLint flags = 0;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(init.glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glfwGetWindowSize(Window, &mWidth, &mHeight);
		mCam.Aspect = mWidth / mHeight;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		ImGui_ImplGlfw_InitForOpenGL(Window, true);
		ImGui_ImplOpenGL3_Init("#version 130");

		return true;
	}

	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// ---------------------------------------------------------------------------------------------------------
	void App::processInput(GLFWwindow* Window)
	{
		mPlayer.PlayerInput.moveForward = glfwGetKey(Window, mPlayer.keyBoardInput.moveForward) == GLFW_PRESS;
		mPlayer.PlayerInput.moveBackward = glfwGetKey(Window, mPlayer.keyBoardInput.moveBackward) == GLFW_PRESS;
		mPlayer.PlayerInput.moveLeft = glfwGetKey(Window, mPlayer.keyBoardInput.moveLeft) == GLFW_PRESS;
		mPlayer.PlayerInput.moveRight = glfwGetKey(Window, mPlayer.keyBoardInput.moveRight) == GLFW_PRESS;
		mPlayer.PlayerInput.moveJump = glfwGetKey(Window, mPlayer.keyBoardInput.moveJump) == GLFW_PRESS;

		if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			mInWindow = true;
			glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			mInWindow = false;
			glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}


		double newMouseX, newMouseY;
		float deltaX, deltaY;
		glfwGetCursorPos(Window, &newMouseX, &newMouseY);
		if (mFirstMouse)
		{
			mMouseX = newMouseX;
			mMouseY = newMouseY;
			mFirstMouse = false;
		}
		deltaX = (float)(newMouseX - mMouseX);
		deltaY = (float)(mMouseY - newMouseY);
		mMouseX = newMouseX;
		mMouseY = newMouseY;

		if (!mInWindow)
			return;

		mCam.CamInputs.deltaX = deltaX;
		mCam.CamInputs.deltaY = deltaY;
		//mCam.CamInputs.moveForward = glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS;
		//mCam.CamInputs.moveBackward = glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS;
		//mCam.CamInputs.moveDown = glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
		//mCam.CamInputs.moveUp = glfwGetKey(Window, GLFW_KEY_SPACE) == GLFW_PRESS;
		//mCam.CamInputs.moveLeft = glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS;
		//mCam.CamInputs.moveRight = glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS;

	}

	void App::InitResources()
	{
		mRscManager = Resources::ResourceManager::GetInstance();
		Resources::Shader* shader = mRscManager->Create<Resources::Shader>("shader", "");
		ASSERT(shader->SetVertexShader("Resources/Shaders/shader.vert"), "Could not load the vertex shader");
		ASSERT(shader->SetFragmentShader("Resources/Shaders/shader.frag"), "Could not load the fragment shader");
		ASSERT(shader->Link(), "Error while linking the shaders");
		mShaderProgram = shader->GetShaderProgram();

		Resources::Script* PlayerControls = mRscManager->Create<Resources::Script>("PlayerControls", "Resources/Scripts/PlayerControls.py");
		mPlayer = Player(mRscManager);
		mPlayer.PlayerControl->takePlayer(mPlayer.Object, mPlayer.PlayerInput);

		Resources::Texture* catTex = mRscManager->Create<Resources::Texture>("cat", "Resources/Textures/cat.png");
		Resources::Texture* dogTex = mRscManager->Create<Resources::Texture>("dog", "Resources/Textures/dog.png");
		Resources::Texture* wallTex = mRscManager->Create<Resources::Texture>("wall", "Resources/Textures/wall.jpg");
		Resources::Texture* potaTex = mRscManager->Create<Resources::Texture>("potato", "Resources/Textures/potatOS.png");
		Resources::Texture* chocoTex = mRscManager->Create<Resources::Texture>("chocoboTex", "Resources/Textures/chocobo.png");
		Resources::Texture* gordoTex = mRscManager->Create<Resources::Texture>("gordoTex", "Resources/Textures/Gordo.png");
		Resources::Texture* ferdiTex = mRscManager->Create<Resources::Texture>("ferdiTex", "Resources/Textures/ferdinand.png");

		auto start = std::chrono::steady_clock::now();

		//Resources::Model* cubeMesh = mRscManager->Create<Resources::Model>("cubeMesh", "Resources/Obj/cube.obj");
		//Resources::Model* potatOS = mRscManager->Create<Resources::Model>("potatos", "Resources/Obj/potatOS.obj");
		//Resources::Model* chocobo = mRscManager->Create<Resources::Model>("chocobo", "Resources/Obj/chocobo.obj");
		//Resources::Model* gordo = mRscManager->Create<Resources::Model>("gordo", "Resources/Obj/Gordo.obj");
		Resources::Model* ferdinand = mRscManager->Create<Resources::Model>("ferdinand", "Resources/Obj/Ferdinand.obj");
		Resources::Model* capsule = Maths::Primitive::Capsule(20);
		mRscManager->Create<Resources::Model>("capsule", capsule);
		Resources::Model* sphere = Maths::Primitive::Sphere(20);
		mRscManager->Create<Resources::Model>("sphere", sphere);
		Resources::Model* cylinder = Maths::Primitive::Cylinder(20);
		mRscManager->Create<Resources::Model>("cylinder", cylinder);
		Resources::Model* cube = Maths::Primitive::Cube();
		mRscManager->Create<Resources::Model>("cube", cube);

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "elapsed time: " << elapsed_seconds.count() * 1000 << "ms\n";

		mGraph.Objects.push_back(new DataStructure::GameObject(Physics::Transform(Vec3(0.f, 12.0f, 0.f)), LowRenderer::Mesh(sphere, mShaderProgram, dogTex), new Physics::SphereCollider()));
		mGraph.RootChildren.push_back({ mGraph.Objects[mGraph.Objects.size() - 1] });

		mGraph.Objects.push_back(new DataStructure::GameObject(Physics::Transform(Vec3(0.f, 0.f, 0.f), Vec3(20.f, 0.5f, 20.f)), LowRenderer::Mesh(cube, mShaderProgram, wallTex), new Physics::BoxCollider()));
		mGraph.RootChildren.push_back({ mGraph.Objects[mGraph.Objects.size() - 1] });

		mGraph.Objects.push_back(new DataStructure::GameObject(Physics::Transform(Vec3(0.f, 1.f, -6.f), Vec3(3.f, 0.25f, 10.f), Vec3(15.f, 0.f, 0.f)), LowRenderer::Mesh(cube, mShaderProgram, catTex), new Physics::BoxCollider()));
		mGraph.RootChildren.push_back({ mGraph.Objects[mGraph.Objects.size() - 1] });

		mGraph.Objects.push_back(new DataStructure::GameObject(Physics::Transform(Vec3(1.5f, 1.f, 2.f), Vec3(2.f, 2.f, 2.f)), LowRenderer::Mesh(cube, mShaderProgram, potaTex), new Physics::BoxCollider()));
		mGraph.RootChildren.push_back({ mGraph.Objects[mGraph.Objects.size() - 1] });

		mGraph.Objects.push_back(new DataStructure::GameObject(Physics::Transform(Vec3(3.5f, 1.f, 4.f), Vec3(2.f, 2.f, 2.f)), LowRenderer::Mesh(cube, mShaderProgram, gordoTex), new Physics::BoxCollider()));
		mGraph.RootChildren.push_back({ mGraph.Objects[mGraph.Objects.size() - 1] });

		mGraph.Objects.push_back(new DataStructure::GameObject(Physics::Transform(Vec3(2.5f, 1.f, -1.f)), LowRenderer::Mesh(cube, mShaderProgram, chocoTex), new Physics::BoxCollider()));
		mGraph.RootChildren.push_back({ mGraph.Objects[mGraph.Objects.size() - 1] });

		mGraph.Objects.push_back(new DataStructure::GameObject(Physics::Transform(Vec3(15.f, 1.f, 15.f), Vec3(10.f, 10.f, 10.f), Vec3(45.f, 45.f, 45.f)), LowRenderer::Mesh(cube, mShaderProgram, wallTex), new Physics::BoxCollider()));
		mGraph.RootChildren.push_back({ mGraph.Objects[mGraph.Objects.size() - 1] });

		mGraph.Objects.push_back(new DataStructure::GameObject(Physics::Transform(Vec3(-5.f, 2.f, -5.f)), LowRenderer::Mesh(capsule, mShaderProgram, wallTex)));
		mGraph.RootChildren.push_back({ mGraph.Objects[mGraph.Objects.size() - 1] });

		mPlayer.Object = mGraph.Objects[0];

		mDirectionalLights.push_back(LowRenderer::DirectionalLight(Vec3(-1.f, -1.f, -1.f)));

		for (DataStructure::GameObject* obj : mGraph.Objects)
		{
			if (obj->Collider)
				obj->Collider->ComputeBoundaries(obj->Transform);
		}

		mSpotLights.push_back(LowRenderer::SpotLight(Vec3(), Vec3(), cosf(20.f * M_PI / 180.f), cosf(40.f * M_PI / 180.f), Vec4(1.f, 1.f, 1.f), Vec4(1.f, 1.f, 1.f), Vec4(1.f, 1.f, 1.f), Vec3(1.f, 0.045f, 0.0075f)));
	}

	void App::DisplaySliderFloatPosObject(std::vector<DataStructure::SceneNode> &Children, std::string index)
	{
		if (Children.size() > 0)
		{
			std::string name = "object";
			for (int j = 0; j < Children.size(); j++)
			{
				ImGui::DragFloat3((name + index + std::to_string(j)).c_str(), &Children[j].Object->Transform.Position.x, 0.5f, -10.f, 10.f, "%.3f", 0);
				DisplaySliderFloatPosObject(Children[j].Children, index + std::to_string(j));
			}
		}
	}

	void App::Update()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		float currentFrame = glfwGetTime();
		mDeltaTime = currentFrame - mLastFrame;
		mLastFrame = currentFrame;
		glfwPollEvents();

		glfwGetWindowSize(Window, &mWidth, &mHeight);
		mCam.Aspect = (float)mWidth / (float)mHeight;
		if (mMenu.gameState == GS_PLAY)
		{
			processInput(Window);
			if (ImGui::Begin("Config"))
			{
				ImGui::Checkbox("Gravity", &mGravity);
				if (ImGui::CollapsingHeader("Player", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::InputFloat3("Velocity", &mPlayer.Object->Velocity.x, "%.3f", 0);
					ImGui::Checkbox("Slide ramp", &mSlide);
				}
				if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::InputFloat3("Pos Camera", &mCam.Position.x, "%.3f", 0);
				}

				if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::ColorEdit3("ColorLight", &mDirectionalLights[0].DiffuseColor.x);
				}

				std::string name = "object";
				if (ImGui::CollapsingHeader("PosObj", ImGuiTreeNodeFlags_DefaultOpen))
				{

					for (int i = 0; i < mGraph.RootChildren.size(); i++)
					{
						ImGui::DragFloat3((name + std::to_string(i)).c_str(), &mGraph.RootChildren[i].Object->Transform.Position.x, 0.5f, -10.f, 10.f, "%.3f", 0);
						DisplaySliderFloatPosObject(mGraph.RootChildren[i].Children, std::to_string(i));
					}

				}
			}
			ImGui::End();

			// input
			// -----

			mCam.Update(mDeltaTime, mPlayer.Object->Transform.Position);

			
			mPlayer.Update(mDeltaTime, mCam);

			// render
			// ------
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			mGraph.Update(mCam, mDirectionalLights, mPointLights, mSpotLights);

			if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				mMenu.gameState = GS_MAIN_MENU;

			for (DataStructure::GameObject* obj : mGraph.Objects)
			{
				if (obj->Collider)
					obj->Collider->ComputeBoundaries(obj->Transform);
			}

			for (DataStructure::GameObject* obj : mGraph.Objects)
			{
				if(obj->Collider && obj->Collider->Type == Physics::ColliderType::COLT_BOX)
					reinterpret_cast<Physics::BoxCollider*>(obj->Collider)->UpdateCollisionData(obj->Mesh.ModelMatrix);

				mPlayer.Object->Collider->ComputeCollision(obj->Collider, obj->Transform.Scale, &mPlayer.Object->Transform.Position);

				if (mPlayer.Object->Collider->IsColliding())
					mPlayer.CanJump = true;
			}

				if (mGravity && !mPlayer.Object->Collider->IsColliding())
					mPlayer.Object->Velocity.y += -9.81f * mDeltaTime;

				if (!mSlide && (!mGravity || mPlayer.Object->Collider->IsColliding()) && mPlayer.CanJump)
					mPlayer.Object->Velocity.y = 0.f;
		}
		else
		{
			ImGui::Begin("Menu", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
			ImGui::SetWindowPos(ImVec2(0, 0), 0);
			ImGui::SetWindowSize(ImVec2(mWidth, mHeight), 0);
			mMenu.Render(Window, mWidth, mHeight);
			
			ImGui::End();
		}

		if (mMenu.gameState == GS_OPTION)
		{
			ImGui::Begin("Option", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
			ImGui::SetWindowSize(ImVec2(mWidth, mHeight), 0);
			ImGui::SetWindowPos(ImVec2(0, 0), 0);
			mMenu.RenderOption(mPlayer, Window,mWidth, mHeight);
			if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				mMenu.gameState = GS_MAIN_MENU;
			ImGui::End();
		}

		ImGui::Render();
		ImGui::EndFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(Window);
	}
}