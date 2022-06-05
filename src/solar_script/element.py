from __future__ import annotations

from typing import Tuple
from dataclasses import dataclass
from transformations import Transformation


@dataclass
class Element:
    file: str
    elements: Tuple[Element] = tuple()
    transformations: Tuple[Transformation] = tuple()
    texture: str = None
