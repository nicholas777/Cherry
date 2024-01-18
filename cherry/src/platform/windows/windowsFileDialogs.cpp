#include "epch.h"
#include "windowsFileDialogs.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "core/application.h"

namespace Cherry
{
    std::string WindowsFileDialogManager::OpenFileImpl(const char* filter)
    {
        HWND win = glfwGetWin32Window((GLFWwindow*)Application::GetApplication().GetWindow()->GetNativeWindow());

        OPENFILENAMEA opendialog = { 0 };
        char szFile[260] = { 0 };
        char currentDir[260] = { 0 };

        opendialog.lStructSize = sizeof(opendialog);
        opendialog.hwndOwner = win;
        opendialog.hInstance = GetModuleHandle(NULL);

        opendialog.lpstrFile = szFile;
        opendialog.nMaxFile = sizeof(szFile);

        opendialog.lpstrFilter = filter;
        opendialog.nFilterIndex = 1;

        if (GetCurrentDirectoryA(256, currentDir))
            opendialog.lpstrInitialDir = currentDir;

        opendialog.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            
        if (GetOpenFileNameA(&opendialog) == TRUE)
        {
            return opendialog.lpstrFile;
        }
        
        return std::string();
    }

    std::string WindowsFileDialogManager::SaveFileImpl(const char* filter)
    {
        OPENFILENAMEA opendialog;
        char szFile[260] = { 0 };
        char currentDir[256] = { 0 };
        ZeroMemory(&opendialog, sizeof(OPENFILENAME));

        opendialog.lStructSize = sizeof(OPENFILENAME);
        opendialog.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::GetApplication().GetWindow()->GetNativeWindow());

        opendialog.lpstrFile = szFile;
        opendialog.nMaxFile = sizeof(szFile);
        if (GetCurrentDirectoryA(256, currentDir))
            opendialog.lpstrInitialDir = currentDir;

        opendialog.lpstrFilter = filter;
        opendialog.nFilterIndex = 1;
        opendialog.lpstrDefExt = std::string(filter).substr(std::string(filter).find_last_of('.') + 1).c_str();
        
        opendialog.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

        if (GetSaveFileNameA(&opendialog) == TRUE)
        {
            return opendialog.lpstrFile;
        }
            
        return std::string();
    }
}
