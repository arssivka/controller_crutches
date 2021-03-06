#pragma once


#include <atomic>
#include <memory>
#include <boost/program_options.hpp>
#include <config/command_arguments_t.h>
#include <config/action_configuration_file_loader_t.h>
#include <config/strategies/ball_searcher_configuration_strategy_t.h>
#include <config/strategies/ball_tracker_configuration_strategy_t.h>
#include <config/strategies/game_controller_configuration_strategy_t.h>
#include <config/strategies/head_configuration_strategy_t.h>
#include <config/strategies/debug_mode_arguments_parsing_strategy_t.h>
#include <config/strategies/config_path_arguments_parsing_strategy_t.h>
#include <config/strategies/help_arguments_parsing_strategy_t.h>
#include <hw/image_source_t.h>
#include <config/strategies/white_ball_vision_processor_arguments_parsing_strategy_t.h>
#include <config/strategies/white_ball_vision_processor_configuration_strategy_t.h>
#include <config/strategies/localization_field_configuration_strategy_t.h>
#include <config/strategies/particle_filter_configuration_strategy_t.h>
#include <behavior/behavior_t.h>
#include <config/strategies/go_to_configuration_strategy_t.h>
#include <config/strategies/kicking_configuration_strategy_t.h>
#include <config/strategies/ball_follower_configuration_strategy_t.h>
#include "config/configuration_file_loader_t.h"
#include "config/strategies/walking_configuration_strategy_t.h"
#include "config/strategies/motion_manager_configuration_strategy_t.h"
#include "hw/linux_motion_timer_t.h"
#include "hw/CM730_t.h"

#ifdef CROSSCOMPILE
#include "hw/linux_CM730_t.h"
#include <hw/robot_image_source_t.h>
#include "config/strategies/robot_image_source_configuration_strategy_t.h"
#else
#include "hw/vrep_image_source_t.h"
#include "hw/vrep_connector_t.h"
#endif

namespace drwn {
    enum exec_status {
        EXEC_SUCCESS = 0,
        EXEC_FAILED = 1
    };

    class robot_application_t {
    public:
        static constexpr char U2D_DEV_NAME0[]{"/dev/ttyUSB0"};
        static constexpr char DEFAULT_MOTION_FILE[]{"res/motion_4096.bin"};
        static constexpr char DEFAULT_CONFIG_FILE[]{"res/config.ini"};

        static robot_application_t* get_instance();

        void set_program_arguments(const command_arguments_t& arguments);

        int exec();

        void stop();

        bool is_running() const;

        bool is_debug_enabled() const noexcept;

        void enable_debug(bool debug) noexcept;

    private:
        robot_application_t() = default;

        bool help_message_requested() const noexcept;

        bool try_start();

        void start_main_loop();

        //*** Initialization methods ***//
        void init_cat();

        void check_hw_status();

        void initialize();

        void init_CM730();

        void check_firmware();

        void init_cv();

        void init_localization();

        void init_motion_manager();

        void init_motion_modules();

        void init_motion_timer();

        void init_game_controller();

        void init_configuraion_loader();

        void parse_command_line_arguments();

        void apply_debug_arguments();

        void read_configuration();

        void init_behavior();

        //TODO: in behavior
        void step_localization();

    private:
        bool m_debug{false}; // Debug output to console

        command_arguments_t m_arguments;

        std::atomic<bool> m_started{ATOMIC_VAR_INIT(false)};
        std::unique_ptr<CM730_t> m_cm730{nullptr};
        std::unique_ptr<linux_motion_timer_t> m_motion_timer{nullptr};
        std::unique_ptr<white_ball_vision_processor_t> m_vision_processor{nullptr};
        std::unique_ptr<particle_filter_t> m_particle_filter{nullptr};
        std::unique_ptr<behavior_t> m_behavior{nullptr};

        //*** Configuration members ***//
        configuration_file_loader_t m_configuration_loader;

        ball_searcher_configuration_strategy_t m_ball_searcher_configuration_strategy;
        ball_tracker_configuration_strategy_t m_ball_tracker_configuration_strategy;
        ball_follower_configuration_strategy_t m_ball_follower_configuration_stratey;
        game_controller_configuration_strategy_t m_game_controller_configuration_strategy;
        head_configuration_strategy_t m_head_configuration_strategy;
        walking_configuration_strategy_t m_walking_configuration_strategy;
        motion_manager_configuration_strategy_t m_motion_manager_configuration_strategy;
        white_ball_vision_processor_configuration_strategy_t m_white_ball_vision_processor_configuration_strategy;
        localization_field_configuration_strategy_t m_localization_field_configuration_strategy;
        particle_filter_configuration_strategy_t m_particle_filter_configuration_strategy;
        go_to_configuration_strategy_t m_go_to_configuration_strategy;
        kicking_configuration_strategy_t m_kicking_configuration_strategy;


        //*** Command line parsing strategies ***//
        help_arguments_parsing_strategy_t m_arg_help_requested;

        debug_mode_arguments_parsing_strategy_t m_arg_debug_all;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_application;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_game_controller;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_motion_manager;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_head;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_walking;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_action;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_kicking;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_buttons;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_leds;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_camera;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_image_source;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_vision_processor;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_localization;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_field;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_ball_tracker;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_ball_searcher;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_ball_follower;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_go_to;
        debug_mode_arguments_parsing_strategy_t m_arg_debug_behavior;

        config_path_arguments_parsing_strategy_t m_arg_config_default;
        config_path_arguments_parsing_strategy_t m_arg_config_game_controller;
        config_path_arguments_parsing_strategy_t m_arg_config_motion_manager;
        config_path_arguments_parsing_strategy_t m_arg_config_head;
        config_path_arguments_parsing_strategy_t m_arg_config_walking;
        config_path_arguments_parsing_strategy_t m_arg_config_action;
        config_path_arguments_parsing_strategy_t m_arg_config_kicking;
        config_path_arguments_parsing_strategy_t m_arg_config_image_source;
        config_path_arguments_parsing_strategy_t m_arg_config_white_ball_vision_processor;
        config_path_arguments_parsing_strategy_t m_arg_config_localization_field;
        config_path_arguments_parsing_strategy_t m_arg_config_particle_filter;
        config_path_arguments_parsing_strategy_t m_arg_config_ball_searcher;
        config_path_arguments_parsing_strategy_t m_arg_config_ball_tracker;
        config_path_arguments_parsing_strategy_t m_arg_config_ball_follower;
        config_path_arguments_parsing_strategy_t m_arg_config_go_to;

        action_configuration_file_loader_t m_action_configuration_loader;
        white_ball_vision_processor_arguments_parsing_strategy_t m_arg_white_ball_vision_processor;

        //*** Platform specific members ***//

#ifdef CROSSCOMPILE
        std::unique_ptr<linux_CM730_t> m_linux_cm730{nullptr};
        std::unique_ptr<robot_image_source_t> m_image_source{nullptr};
        robot_image_source_configuration_strategy_t m_robot_image_source_configuration_strategy;
#else
        std::unique_ptr<vrep_image_source_t> m_image_source{nullptr};
        std::unique_ptr<vrep_connector_t> m_vrep_connector{nullptr};
#endif
    };
}


