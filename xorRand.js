// https://en.wikipedia.org/wiki/Xorshift
function getXorRand(seed) {
	seed = seed || new Date().getTime();
	let w = 0;
	
	// Set up generator function.
	function xor() {
		let t = seed ^ (seed << 11);
		w ^= (w >> 19) ^ t ^ (t >> 8);
		seed = w;
		return seed / max32BitInt;
	}
	
	// discard first 64 vals
	for (let k = 64; k > 0; --k) {
		xor();
	}
	
	return xor;
}

module.exports = getXorRand;