#include "HittableCollection.h"

using namespace std;

bool HittableCollection::Hit(const Ray& rRay, double rayTimeMin, double rayTimeMax, HitInfo& hitInfo) const {
	HitInfo tempInfo;
	bool hasHit = false;
	auto closestHit = rayTimeMax;

	for (const shared_ptr<Hittable>& hittable : mPool) {
		if (hittable->Hit(rRay, rayTimeMin, closestHit, tempInfo)) {
			hasHit = true;
			closestHit = tempInfo.time;
			hitInfo = tempInfo;
		}
	}

	return hasHit;
}