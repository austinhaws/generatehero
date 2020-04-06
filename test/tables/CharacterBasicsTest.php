<?php
namespace Heroes\tests\tables;

use Heroes\hero\Hero;
use Heroes\tables\CharacterBasics;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class CharacterBasicsTest extends BaseTestRunner
{
    private $characterBasics;

    function __construct($name = NULL, array $data = array(), $dataName = '')
    {
        parent::__construct($name, $data, $dataName);
        $this->characterBasics = new CharacterBasics($this->engine);
    }

    public function testGenerateCharacterBasics()
    {
        $hero = new Hero();

        $this->engine->roller->setTestRolls([
            new TestRoll(100, 30, 'birth order'),
            new TestRoll(100, 30, 'weight'),
            new TestRoll(100, 30, 'height'),
            new TestRoll(100, 30, 'disposition'),
            new TestRoll(100, 30, 'life savings'),
            new TestRoll(100, 30, 'land of origin'),
            new TestRoll(100, 30, 'environment'),
            new TestRoll(100, 30, 'social/economic background'),
            new TestRoll(100, 30, 'when manifested'),
            new TestRoll(108, 30, 'Age'),
            new TestRoll(5, 4, 'Late Teen'),
        ]);

        $this->characterBasics->generateCharacterBasics($hero);

        $this->assertNotNull($hero->birthOrder, 'birth order');
        $this->assertNotNull($hero->weight, 'weight');
        $this->assertNotNull($hero->height, 'height');
        $this->assertNotNull($hero->disposition, 'disposition');
        $this->assertNotNull($hero->landOfOrigin, 'land of origin');
        $this->assertNotNull($hero->environment, 'environment');
        $this->assertNotNull($hero->socialEconomic, 'social economioc');
        $this->assertNotNull($hero->whenManifested, 'when manifested');
        $this->assertNotNull($hero->age, 'age');

        $this->engine->roller->verifyTestRolls();
    }

}
