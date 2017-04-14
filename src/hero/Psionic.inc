<?php
namespace Heroes\hero;


class Psionic
{
    public $title;
    public $range;
    public $duration;
    public $isp;
    public $savingThrow;
    public $description;

    public function __construct($title, $range, $duration, $isp, $savingThrow, $description)
    {
        $this->title = $title;
        $this->range = $range;
        $this->duration = $duration;
        $this->isp = $isp;
        $this->savingThrow = $savingThrow;
        $this->description = $description;
    }


}