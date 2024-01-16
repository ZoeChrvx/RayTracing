#include "Camera.h"
using namespace std;

void Camera::Render(const Hittable& rWorld) {
	cout << "P3\n" << width << ' ' << height << "\n255\n";
	for (int y = 0; y < height; y++) {
		clog << "Progress : " << (y * 100 / height) << " %\n" << flush;
		for (int x = 0; x < width; x++) {
			Position pixelCenter = originPixelLocation + (x * pixelDeltaX) + (y * pixelDeltaY);
			Vector3 direction = pixelCenter - center;
			Ray ray(center, direction);
			Color pixel = RayColor(ray, rWorld);
			WriteColor(cout, pixel);
		}
	}
	clog << "Done! You can open your file now :)\n";
}

void Camera::Initialize() {
	height = static_cast<int>(width / aspectRatio);
	if (height < 1) height = 1;

	center = Position(0, 0, 0);
	double focalLength = 1;
	double viewportHeight = 2;
	double viewportWidth = viewportHeight * (static_cast<double>(width) / height);

	Vector3 viewportX = Vector3(viewportWidth, 0, 0);
	Vector3 viewportY = Vector3(0, -viewportHeight, 0); //We invert Y

	//Delta vector between pixels
	pixelDeltaX = viewportX / width;
	pixelDeltaY = viewportY / height;

	//Position of the top left pixel
	Vector3 viewportOrigin = center - Vector3(0, 0, focalLength)
		- viewportX / 2 - viewportY / 2;

	originPixelLocation = viewportOrigin + 0.5 * (pixelDeltaX + pixelDeltaY);
}

Color Camera::RayColor(const Ray& rRay, const Hittable& rWorld) const {
	HitInfo hitInfo;
	if (rWorld.Hit(rRay, Interval(0, infinity), hitInfo)) {
		return 0.5 * (hitInfo.normal + Color(1, 1, 1));
	}
	Vector3 unitDirection = Unit(rRay.GetDirection());
	double blue = 0.5 * (unitDirection.y + 1.0);
	return (1.0 - blue) * Color(1.0, 1.0, 1.0) + blue * Color(0.5, 0.7, 1.0);
}
