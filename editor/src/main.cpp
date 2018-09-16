#include <Window.h>

int main(){

    yage::WindowDesc desc;
    desc.floating = true;

    yage::Window window(desc);

    while(!window.shouldClose()){
        window.update();
    }
    return 0;
}
