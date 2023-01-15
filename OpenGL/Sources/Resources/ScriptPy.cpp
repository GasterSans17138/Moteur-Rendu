#include <Resources/ScriptPy.hpp>


namespace Resources
{
    Script::Script(const char* path)
    {
        LoadData(path);
    }

    Script::Script()
    {

    }

    Script::~Script()
    {
    }

    const char* Script::ParseModuleName(const char* path)
    {
        std::string moduleStr = std::string(path);
        size_t dotIdx = moduleStr.find_last_of(".");
        moduleStr = moduleStr.substr(0, dotIdx);

        size_t slahsidx = moduleStr.find_last_of("/");
        moduleStr = moduleStr.substr(slahsidx + 1, moduleStr.back());
                
        const char* moduleName = moduleStr.c_str();

        return moduleName;
    }

    void Script::LoadData(const char* path)
    {
        const char * moduleName = Script::ParseModuleName(path);


        scriptModule = pybind11::module::import("PlayerControls");
        scriptObj = scriptModule.attr("PlayerControls")(Object, PlayerInput);
    }

    void Script::Update(const float deltaTime, const LowRenderer::Camera& cam)
    {
        try
        {
            scriptObj.attr("Update")(deltaTime, cam);
        }
        catch (pybind11::error_already_set& e)
        {
            if (e.matches(PyExc_AttributeError)) {
                //pybind11::print("Pb Runtime==============================");
            }
            else {
                throw;
            }
        }
    }
}