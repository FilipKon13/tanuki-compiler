
const puppeteer = require('puppeteer');
async function start() {
    const browser = await puppeteer.launch({headless: false});
    const page = await browser.newPage();
    async function clickXPath(xPath) {
    const [el] = await page.$x(xPath);
    await el.click();
  };

  async function clickTimes(xPath, times) {
    const [el] = await page.$x(xPath);
    await el.click({clickCount: times});
  }

  async function clickContaining(text) {
    await clickXPath(`//*[contains(text(), "${text}")]`);
  };

  async function typeXPath(xPath, text) {
      const [el] = await page.$x(xPath);
      await el.type(text);
  }

  async function waitForXPath(xPath) {
    await page.waitForXPath(xPath, {timeout: 0});
  }

  async function load(url) {
    await page.goto(url);
  }

  async function press(key) {
    await page.keyboard.press(key);
  }

  async function getText(XPath) {
    await page.waitForXPath(XPath, {timeout:0})
    const [getXpath] = await page.$x(XPath);
    return await page.evaluate(name => name.textContent, getXpath);
  }

  async function wait(milis) {
    await page.waitForTimeout(milis);
  }

  async function print(smth) {
    console.log(smth);
  }

  async function repeat(times, fun) {
    for(let i = 0; i < times; ++i) {
      fun();
    }
  }

	await load('https://www.facebook.com/');
	await clickXPath('/html/body/div[3]/div[2]/div/div/div/div/div[4]/button[2]');
	await typeXPath('/html/body/div[1]/div[1]/div[1]/div/div/div/div[2]/div/div[1]/form/div[1]/div[1]/input', 'tanuki.testt@gmail.com');
	await typeXPath('/html/body/div[1]/div[1]/div[1]/div/div/div/div[2]/div/div[1]/form/div[1]/div[2]/div/input', 'tanuki123!');
	await clickXPath('/html/body/div[1]/div[1]/div[1]/div/div/div/div[2]/div/div[1]/form/div[2]/button');
	await waitForXPath('/html/body/div[1]/div/div[1]/div/div[3]/div/div/div/div[1]/div[1]/div/div[2]');
	await clickXPath('/html/body/div[1]/div/div[1]/div/div[3]/div/div/div/div[1]/div[1]/div/div[2]');
	await clickXPath('/html/body/div[1]/div/div[1]/div/div[2]/div[4]/div/div[1]/div[1]/ul/li[3]/span/div/a');
	await waitForXPath('/html/body/div[1]/div/div[1]/div/div[3]/div/div/div/div[1]/div[1]/div[1]/div/div[3]/div[1]/div[5]/div/div/div/div/a');
	await clickXPath('/html/body/div[1]/div/div[1]/div/div[3]/div/div/div/div[1]/div[1]/div[1]/div/div[3]/div[1]/div[5]/div/div/div/div/a');
	await waitForXPath('/html/body/div[1]/div/div[1]/div/div[3]/div/div/div/div[1]/div[1]/div[2]/div/div/div/div[4]/div/div[2]/div/div/div/div[2]/div/div[2]/div/div/div/div/div/div/div/div/div/div[2]/div/div/div[4]/div/div/div[1]/div/div[2]/div/div[2]/div');
	await clickXPath('/html/body/div[1]/div/div[1]/div/div[3]/div/div/div/div[1]/div[1]/div[2]/div/div/div/div[4]/div/div[2]/div/div/div/div[2]/div/div[2]/div/div/div/div/div/div/div/div/div/div[2]/div/div/div[4]/div/div/div[1]/div/div[2]/div/div[2]/div');
	await waitForXPath('/html/body/div[1]/div/div[1]/div/div[4]/div/div/div[1]/div/div[2]/div/div/div/div/div/div/div[3]/div/div/div/div/div/div[1]/div/div/div/div[2]/div[1]/form/div/div[1]/div[1]/div/div[1]');
	for (i of ['100', '200', '300', '400', '500'])
	{
		await wait(500);
		await typeXPath('/html/body/div[1]/div/div[1]/div/div[4]/div/div/div[1]/div/div[2]/div/div/div/div/div/div/div[3]/div/div/div/div/div/div[1]/div/div/div/div[2]/div[1]/form/div/div[1]/div[1]/div/div[1]', 'Comment ' + i);
		await wait(500);
		await press('Enter');
	}
}

exports.start = start;
