-- Load a different tilemap image depending on the current system time
local current_system_hour = os.date("*t").hour

-- Use a day-map or night-map texture (9am - 6pm)
local map_texture_asset_id
if current_system_hour >= 9 and current_system_hour < 18 then
    map_texture_asset_id = "tilemap-texture-day"
else
    map_texture_asset_id = "tilemap-texture-night"
end

-- Define a table with the start values of the first level
Level = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] =
        { type = "texture", id = "tilemap-texture-day",         file = "./assets/tilemaps/jungle.png" },
        { type = "texture", id = "tilemap-texture-night",       file = "./assets/tilemaps/jungle-night.png" },
        { type = "texture", id = "chopper-texture",             file = "./assets/images/chopper-green-spritesheet.png" },
        { type = "texture", id = "su27-texture",                file = "./assets/images/su27-spritesheet.png" },
        { type = "texture", id = "f22-texture",                 file = "./assets/images/f22-spritesheet.png" },
        { type = "texture", id = "fw190-texture",               file = "./assets/images/fw190-spritesheet.png" },
        { type = "texture", id = "upf7-texture",                file = "./assets/images/upf7-spritesheet.png" },
        { type = "texture", id = "bf109-texture",               file = "./assets/images/bf109-spritesheet.png" },
        { type = "texture", id = "bomber-texture",              file = "./assets/images/bomber-spritesheet.png" },
        { type = "texture", id = "carrier-texture",             file = "./assets/images/carrier.png" },
        { type = "texture", id = "boat-texture",                file = "./assets/images/boat.png" },
        { type = "texture", id = "tank-tiger-up-texture",       file = "./assets/images/tank-tiger-up.png" },
        { type = "texture", id = "tank-tiger-right-texture",    file = "./assets/images/tank-tiger-right.png" },
        { type = "texture", id = "tank-tiger-down-texture",     file = "./assets/images/tank-tiger-down.png" },
        { type = "texture", id = "tank-tiger-left-texture",     file = "./assets/images/tank-tiger-left.png" },
        { type = "texture", id = "tank-tiger-killed-texture",   file = "./assets/images/tank-tiger-killed.png" },
        { type = "texture", id = "tank-panther-up-texture",     file = "./assets/images/tank-panther-up.png" },
        { type = "texture", id = "tank-panther-right-texture",  file = "./assets/images/tank-panther-right.png" },
        { type = "texture", id = "tank-panther-down-texture",   file = "./assets/images/tank-panther-down.png" },
        { type = "texture", id = "tank-panther-left-texture",   file = "./assets/images/tank-panther-left.png" },
        { type = "texture", id = "tank-panther-killed-texture", file = "./assets/images/tank-panther-killed.png" },
        { type = "texture", id = "truck-ford-up-texture",       file = "./assets/images/truck-ford-up.png" },
        { type = "texture", id = "truck-ford-right-texture",    file = "./assets/images/truck-ford-right.png" },
        { type = "texture", id = "truck-ford-down-texture",     file = "./assets/images/truck-ford-down.png" },
        { type = "texture", id = "truck-ford-left-texture",     file = "./assets/images/truck-ford-left.png" },
        { type = "texture", id = "truck-ford-killed-texture",   file = "./assets/images/truck-ford-killed.png" },
        { type = "texture", id = "army-walk-up-texture",        file = "./assets/images/army-walk-up.png" },
        { type = "texture", id = "army-walk-right-texture",     file = "./assets/images/army-walk-right.png" },
        { type = "texture", id = "army-walk-down-texture",      file = "./assets/images/army-walk-down.png" },
        { type = "texture", id = "army-walk-left-texture",      file = "./assets/images/army-walk-left.png" },
        { type = "texture", id = "army-walk-killed-texture",    file = "./assets/images/army-walk-killed.png" },
        { type = "texture", id = "army-gun-up-texture",         file = "./assets/images/army-gun-up.png" },
        { type = "texture", id = "army-gun-right-texture",      file = "./assets/images/army-gun-right.png" },
        { type = "texture", id = "army-gun-down-texture",       file = "./assets/images/army-gun-down.png" },
        { type = "texture", id = "army-gun-left-texture",       file = "./assets/images/army-gun-left.png" },
        { type = "texture", id = "army-gun-killed-texture",     file = "./assets/images/army-gun-killed.png" },
        { type = "texture", id = "sam-truck-right-texture",     file = "./assets/images/sam-truck-right.png" },
        { type = "texture", id = "sam-tank-left-texture",       file = "./assets/images/sam-tank-left-spritesheet.png" },
        { type = "texture", id = "sam-tank-right-texture",      file = "./assets/images/sam-tank-right-spritesheet.png" },
        { type = "texture", id = "takeoff-base-texture",        file = "./assets/images/takeoff-base.png" },
        { type = "texture", id = "landing-base-texture",        file = "./assets/images/landing-base.png" },
        { type = "texture", id = "runway-texture",              file = "./assets/images/runway.png" },
        { type = "texture", id = "obstacles1-texture",          file = "./assets/images/obstacles-1.png" },
        { type = "texture", id = "obstacles2-texture",          file = "./assets/images/obstacles-2.png" },
        { type = "texture", id = "obstacles3-texture",          file = "./assets/images/obstacles-3.png" },
        { type = "texture", id = "obstacles4-texture",          file = "./assets/images/obstacles-4.png" },
        { type = "texture", id = "obstacles5-texture",          file = "./assets/images/obstacles-5.png" },
        { type = "texture", id = "obstacles6-texture",          file = "./assets/images/obstacles-6.png" },
        { type = "texture", id = "obstacles7-texture",          file = "./assets/images/obstacles-7.png" },
        { type = "texture", id = "tree1-texture",               file = "./assets/images/tree-1.png" },
        { type = "texture", id = "tree2-texture",               file = "./assets/images/tree-2.png" },
        { type = "texture", id = "tree3-texture",               file = "./assets/images/tree-3.png" },
        { type = "texture", id = "tree4-texture",               file = "./assets/images/tree-4.png" },
        { type = "texture", id = "tree5-texture",               file = "./assets/images/tree-5.png" },
        { type = "texture", id = "tree6-texture",               file = "./assets/images/tree-6.png" },
        { type = "texture", id = "tree7-texture",               file = "./assets/images/tree-7.png" },
        { type = "texture", id = "tree8-texture",               file = "./assets/images/tree-8.png" },
        { type = "texture", id = "tree9-texture",               file = "./assets/images/tree-9.png" },
        { type = "texture", id = "tree10-texture",              file = "./assets/images/tree-10.png" },
        { type = "texture", id = "tree11-texture",              file = "./assets/images/tree-11.png" },
        { type = "texture", id = "tree12-texture",              file = "./assets/images/tree-12.png" },
        { type = "texture", id = "tree13-texture",              file = "./assets/images/tree-13.png" },
        { type = "texture", id = "tree14-texture",              file = "./assets/images/tree-14.png" },
        { type = "texture", id = "tree15-texture",              file = "./assets/images/tree-15.png" },
        { type = "texture", id = "tree16-texture",              file = "./assets/images/tree-16.png" },
        { type = "texture", id = "tree17-texture",              file = "./assets/images/tree-17.png" },
        { type = "texture", id = "tree18-texture",              file = "./assets/images/tree-18.png" },
        { type = "texture", id = "tree19-texture",              file = "./assets/images/tree-19.png" },
        { type = "texture", id = "tree20-texture",              file = "./assets/images/tree-20.png" },
        { type = "texture", id = "bullet-texture",              file = "./assets/images/bullet.png" },
        { type = "texture", id = "radar-texture",               file = "./assets/images/radar-spritesheet.png" },
        { type = "font"   , id = "pico8-font-5",                file = "./assets/fonts/pico8.ttf", font_size = 5 },
        { type = "font"   , id = "pico8-font-10",               file = "./assets/fonts/pico8.ttf", font_size = 10 }
    },

    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    tilemap = {
        map_file = "./assets/tilemaps/jungle.map",
        texture_asset_id = map_texture_asset_id,
        num_rows = 20,
        num_cols = 25,
        tile_size = 32,
        scale = 2.0
    },

    ----------------------------------------------------
    -- table to define entities and their components
    ----------------------------------------------------
    entities = {
        [0] =
        {
            -- Player
            tag = "player",
            components = {
                transform = {
                    position = { x = 242, y = 110 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "chopper-texture",
                    width = 32,
                    height = 32,
                    z_index = 4,
                    fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 25,
                    offset = { x = 0, y = 5 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = 200, y = 200 },
                    projectile_duration = 10, -- seconds
                    repeat_frequency = 0, -- seconds
                    hit_percentage_damage = 10,
                    friendly = true
                },
                keyboard_controller = {
                    velocity = { x = 50, y = 50 }
                },
                camera_follow = {
                    follow = true
                }
            }
        }
    }
}

-- Define some useful global variables
map_width = Level.tilemap.num_cols * Level.tilemap.tile_size * Level.tilemap.scale
map_height = Level.tilemap.num_rows * Level.tilemap.tile_size * Level.tilemap.scale
