#ifndef KASPERSKYTEST_SUSPICIONS_H
#define KASPERSKYTEST_SUSPICIONS_H

#include <string_view>
#include <array>

namespace Suspicions
{
    enum class SuspicionType;

    struct Suspicion {
        constexpr Suspicion(SuspicionType suspicionType, const std::string_view& suspicion)
        : suspicionType{ suspicionType },
        suspicion{ suspicion }
        {}

        const SuspicionType suspicionType;
        const std::string_view suspicion;
    };

    enum class SuspicionType
    {
        None = -1
        , JsSuspicion
        , UnixSuspicion
        , MacOsSuspicion
    };

    constexpr int suspicionCount = 3;
    constexpr std::array<Suspicion, suspicionCount> suspicionArray = {
            Suspicion{SuspicionType::JsSuspicion, "<script>evil_script()</script>"}
            , Suspicion{SuspicionType::UnixSuspicion, "rm -rf ~/Documents"}
            , Suspicion{SuspicionType::MacOsSuspicion, "system(\"launchctl load /Library/LaunchAgents/com.malware.agent\")"}
    };
    constexpr std::array<std::string_view, suspicionCount> suspicionNames = {
            "JS"
            , "Unix"
            , "macOS"
    };
    /**
     * In order to add new "suspicions", we only need:
     * 1) Add new "SuspicionType"
     * 2) Increase "suspicionCount"
     * 3) Add new pair in "suspicionArray"
     * 4) Add new suspicionName in "suspicionNames"
     */
}

#endif //KASPERSKYTEST_SUSPICIONS_H
