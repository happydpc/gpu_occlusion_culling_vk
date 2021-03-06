#pragma once
#include "Prog_info.hpp"

class Shell : public base::Shell_base
{
public:
    float orbit_speed = 0.01f;
    float zoom_speed = 0.03f;
    float pan_speed = 0.1f;

    Shell(Prog_info* p_info,
          base::Camera* p_camera) :
        Shell_base(p_info),
        p_camera_(p_camera),
        p_info_(p_info)
    {}

    void on_key(base::Key key) override
    {
        switch (key) {
            // orbit(zoom, phi, theta)
            case base::KEY_UP:p_camera_->orbit(0.f, orbit_speed, 0.f);
                break;
            case base::KEY_DOWN:p_camera_->orbit(0.f, -orbit_speed, 0.f);
                break;
            case base::KEY_LEFT:p_camera_->orbit(0.f, 0.f, -orbit_speed);
                break;
            case base::KEY_RIGHT:p_camera_->orbit(0.f, 0.f, orbit_speed);
                break;
            case base::KEY_WHEEL_UP:p_camera_->orbit(-zoom_speed, 0.f, 0.f);
                break;
            case base::KEY_WHEEL_DOWN:p_camera_->orbit(zoom_speed, 0.f, 0.f);
                break;

            case base::KEY_A:p_camera_->pan(-pan_speed, 0.f); // pan left 
                break;
            case base::KEY_D:p_camera_->pan(pan_speed, 0.f); // pan right
                break;
            case base::KEY_R:p_camera_->pan(0.f, -pan_speed); // pan up
                break;
            case base::KEY_F:p_camera_->pan(0.f, pan_speed); // pan down
                break;
            case base::KEY_W:p_camera_->forward(-pan_speed); // move forward
                break;
            case base::KEY_S:p_camera_->forward(pan_speed); // move backward
                break;

            case::base::KEY_F1:p_info_->select_mode(1);
                break;
            case::base::KEY_F2:p_info_->select_mode(2);
                break;
            case::base::KEY_F3:p_info_->select_mode(3);
                break;
            case::base::KEY_F4:p_info_->select_mode(4);
                break;

            default:base::Shell_base::on_key(key);
                break;
        }
    }

private:
    base::Camera* p_camera_{nullptr};
    Prog_info *p_info_{nullptr};

    void window_resize_(uint32_t width, uint32_t height) override
    {
        p_info_base_->on_resize(width, height);
        p_camera_->update_aspect(width, height);
    }

    void on_get_minmax_info_(LPARAM lparam) override {
       p_minmax_info_ = reinterpret_cast<MINMAXINFO FAR *>(lparam);
       p_minmax_info_->ptMaxTrackSize.x = p_info_->MAX_DEPTH_IMAGE_WIDTH;
       p_minmax_info_->ptMaxTrackSize.y = p_info_->MAX_DEPTH_IMAGE_HEIGHT;
    }
};
