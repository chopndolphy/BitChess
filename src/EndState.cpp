#include "EndState.h"
#include "Application.h"
#include "Renderer2D.h"

void EndState::Enter() {
    app.Renderer().lock()->ShowMenu(app.AppEndDisplay);
}
void EndState::ProcessClicks() {

}
void EndState::Exit() {

}