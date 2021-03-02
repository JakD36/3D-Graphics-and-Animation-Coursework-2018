//
// Created by Jack Davidson on 26/01/2021.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DRAWRENDERERS_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DRAWRENDERERS_H

class SceneGraph;
class Camera;

class DrawRenderers : public RenderCommand
{
public:
    SceneGraph* m_scene;
    Camera* m_camera;

    DrawRenderers(SceneGraph* scene, Camera* camera) : RenderCommand(Type::DRAW_RENDERERS,1),
        m_camera(camera), m_scene(scene) {}
};

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DRAWRENDERERS_H
