#ifndef APP_STAGE_HMD_SETTINGS_H
#define APP_STAGE_HMD_SETTINGS_H

//-- includes -----
#include "AppStage.h"
#include <vector>
#include <string>

//-- definitions -----
class AppStage_HMDSettings : public AppStage
{
public:
    enum eHMDType
    {
        Morpheus,
        VirtualHMD
    };

    struct HMDInfo
    {
        int HmdID;
        eHMDType HmdType;
        std::string DevicePath;
        PSMTrackingColorType TrackingColorType;
		int PositionFilterIndex;
		std::string PositionFilterName;
		int OrientationFilterIndex;
		std::string OrientationFilterName;
		float PredictionTime;
    };


    AppStage_HMDSettings(class App *app);

    inline const HMDInfo *getSelectedHmdInfo() const
    {
        return
            (m_selectedHmdIndex != -1)
            ? &m_hmdInfos[m_selectedHmdIndex]
            : nullptr;
    }

    virtual void enter() override;
    virtual void exit() override;
    virtual void update() override;
    virtual void render() override;

    virtual void renderUI() override;

    static const char *APP_STAGE_NAME;

protected:
    virtual bool onClientAPIEvent(
        PSMEventMessage::eEventType event, 
        PSMEventDataHandle opaque_event_handle) override;

    void request_hmd_list();
	static void handle_hmd_list_response(
		const PSMResponseMessage *response,
		void *userdata);

	void request_set_orientation_filter(const int hmd_id, const std::string &filter_name);
	void request_set_position_filter(const int hmd_id, const std::string &filter_name);
	void request_set_hmd_prediction(const int hmd_id, float prediction_time);
	void request_set_hmd_tracking_color_id(
		const int hmd_id,
		PSMTrackingColorType tracking_color_type);


private:
    enum eHmdMenuState
    {
        inactive,
        idle,

        pendingHmdListRequest,
        failedHmdListRequest,
    };
    eHmdMenuState m_menuState;

    std::vector<HMDInfo> m_hmdInfos;

    int m_selectedHmdIndex;
};

#endif // APP_STAGE_HMD_SETTINGS_H
