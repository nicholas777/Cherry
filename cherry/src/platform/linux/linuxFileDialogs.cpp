#include "epch.h"

#include "linuxFileDialogs.h"

#include <osdialog.h>

namespace Cherry {
    const char* LinuxFileDialogManager::OpenFileImpl(const char* filter) {
        osdialog_filters* filters = filter ? osdialog_filters_parse(filter) : nullptr;
        char* result = osdialog_file(OSDIALOG_OPEN, NULL, NULL, filters);
        if (filter) osdialog_filters_free(filters);

        return result;
    }

    const char* LinuxFileDialogManager::SaveFileImpl(const char* filter) {
        osdialog_filters* filters = filter ? osdialog_filters_parse(filter) : nullptr;
        char* result = osdialog_file(OSDIALOG_SAVE, NULL, NULL, filters);
        if (filter) osdialog_filters_free(filters);

        return result;
    }
}
